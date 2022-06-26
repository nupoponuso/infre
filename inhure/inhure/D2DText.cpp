#include "D2DText.h"

#include "RenderingEngine.h"	//インスタンスの取得(D2DRenderTargetsAndDWrite, D2DDrawMng)
#include "D2DRenderTargetsAndDWrite.h"
#include "D2DDrawMng.h"


namespace F_lib_Render
{
#pragma region D2DTextHelper
std::wstring D2DText::StringToWString(std::string str)
{
	// SJIS → wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (wchar_t*)NULL, 0);
	// 格納バッファの取得
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];
	// SJIS → wstring (intを再利用して結果取得)
	iBufferSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, cpUCS2, iBufferSize);
	if (iBufferSize == 0) {
		delete[] cpUCS2;
		cpUCS2 = nullptr;
		return nullptr;
	}
	// stringの生成
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);
	// バッファの破棄
	delete[] cpUCS2;
	cpUCS2 = nullptr;
	// 変換結果を返す
	return(oRet);
}
#pragma endregion D2DTextHelper



#pragma region TextLine
	D2DText::D2DText(IDWriteFactory* factory, ID2D1RenderTarget* target)
		//: RenderTargetResources(target)
		: TextLayout(nullptr)
		, Setting(new FontData())
		//, Text()
		//, DrawRect(D2D1_RECT_F{ 0,0,10.0f,10.0f })
		//, DrawOrder(defDrawOrder)
		//, DrawFlag(true)
	{
		//外部インスタンスの取得(今回は場所が特定されているので直接取得している)
		RenderTarget = target;
		RenderTarget->AddRef();
		DWriteFactory = factory;
		DWriteFactory->AddRef();
		//Manager = getEngine()->getD2DTextMng();
		//TextFormat, SolidBrushの生成
		SetFont(Setting);

		// 生成したら即登録
		//Manager->Add(this);
	}

	D2DText::~D2DText()
	{
		//Manager->Remove(this);
		//Manager = nullptr;
		delete Setting;
		Setting = nullptr;
		SAFE_RELEASE(RenderTarget);
		SAFE_RELEASE(DWriteFactory);
		SAFE_RELEASE(TextFormat);
		SAFE_RELEASE(SolidBrush);
		SAFE_RELEASE(TextLayout);
	}

	void D2DText::DrawString(const std::string str, D2D1_POINT_2F pos, D2D1_DRAW_TEXT_OPTIONS options)
	{
		// 文字列の変換
		std::wstring wstr = StringToWString(str.c_str());
		// ターゲットサイズの取得
		D2D1_SIZE_F TargetSize = RenderTarget->GetSize();
		// テキストレイアウトを作成
		DWriteFactory->CreateTextLayout(
			wstr.c_str(), (UINT32)wstr.size(),
			TextFormat, TargetSize.width, TargetSize.height,
			&TextLayout);
		// 描画位置の確定
		D2D1_POINT_2F points;
		points.x = pos.x;
		points.y = pos.y;
		// 描画の開始
		RenderTarget->BeginDraw();
		// 描画処理
		RenderTarget->DrawTextLayout(points, TextLayout, SolidBrush, options);
		// 描画の終了
		RenderTarget->EndDraw();
	}

	void D2DText::DrawString(const std::string str, D2D1_RECT_F rect, D2D1_DRAW_TEXT_OPTIONS options)
	{
		// 文字列の変換
		std::wstring wstr = StringToWString(str.c_str());
		// 描画の開始
		RenderTarget->BeginDraw();
		// 描画処理
		RenderTarget->DrawText(
			wstr.c_str(), (UINT32)wstr.size(),
			TextFormat, rect, SolidBrush, options);
		// 描画の終了
		RenderTarget->EndDraw();
	}

	HRESULT D2DText::SetFont(FontData * set, FontData * out_preFont)
	{
		HRESULT hr = S_OK;

		// 設定済みのフォント情報を取得
		if (TextFormat && out_preFont != nullptr) {
			WCHAR buff[MAXCHAR];
			TextFormat->GetFontFamilyName(buff, MAXCHAR);
			// 使用可能フォントリストに含まれていなければL"メイリオ"を返す
			int num = 0;
			for (auto&& f : FontList) {
				if (wcscmp(f, buff) == 0) {
					out_preFont->font = static_cast<Font>(num);
					break;
				} else {
					out_preFont->font = Font::Meiryo;
				}
				num++;
			}
			TextFormat->GetFontCollection(&out_preFont->fontCollection);
			out_preFont->fontWeight = TextFormat->GetFontWeight();
			out_preFont->fontStyle = TextFormat->GetFontStyle();
			out_preFont->fontStretch = TextFormat->GetFontStretch();
			out_preFont->fontSize = TextFormat->GetFontSize();
			//TextFormat->GetLocaleName(buff, MAXCHAR);	//Note:規定値のみ返している。cosnt wchar_tのサイズ調整しながらコピーする方法がよくわからない
			out_preFont->localeName = L"ja-jp";
			out_preFont->textAlignment = TextFormat->GetTextAlignment();
			out_preFont->Color = SolidBrush->GetColor();
			out_preFont->Opacity = SolidBrush->GetOpacity();
		}

		// 新しいフォント情報を設定
		hr = DWriteFactory->CreateTextFormat(
			FontList[static_cast<int>(set->font)],
			set->fontCollection,
			set->fontWeight,
			set->fontStyle,
			set->fontStretch,
			set->fontSize,
			set->localeName,
			&TextFormat
		);
		if (FAILED(hr))	return hr;
		hr = TextFormat->SetTextAlignment(set->textAlignment);
		if (FAILED(hr)) return hr;
		hr = RenderTarget->CreateSolidColorBrush(set->Color, &SolidBrush);
		if (FAILED(hr)) return hr;
		SolidBrush->SetOpacity(set->Opacity);

		return hr;
	}

	HRESULT D2DText::SetFont(Font font, IDWriteFontCollection * fontCollection,
		DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, 
		DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const * localeName, 
		DWRITE_TEXT_ALIGNMENT textAlignment, D2D1_COLOR_F color, FLOAT opacity
		, FontData* out_preFont)
	{
		FontData fd;
		fd.font = font; fd.fontCollection = fontCollection;	fd.fontWeight = fontWeight;
		fd.fontStyle = fontStyle; fd.fontStretch = fontStretch;	fd.fontSize = fontSize;
		fd.localeName = localeName;	fd.textAlignment = textAlignment;
		fd.Color = color; fd.Opacity = opacity;
		HRESULT hr = SetFont(&fd, out_preFont);
		if (FAILED(hr)) return hr;
		return S_OK;
	}



	//void D2DText::SetText(const std::wstring str)
	//{
	//	Text = str;
	//}

	//void D2DText::SetText(const WCHAR * str, int length)
	//{
	//	Text = std::wstring(str);
	//	//TextLength = length;
	//}

	//void D2DText::SetRect(D2D1_RECT_F rect)
	//{
	//	DrawRect = rect;
	//}

	//void D2DText::SerDrawOrder(int drawOrder)
	//{
	//	Manager->ChangeDrawOrder(this, drawOrder);
	//	DrawOrder = drawOrder;
	//}

	//void D2DText::SetDrawFlag(bool enable)
	//{
	//	DrawFlag = enable;
	//}

	//void D2DText::SetFontSize(float size)
	//{
	//	//WCHAR pre_font[MAXCHAR];
	//	//TextFormat->GetFontFamilyName(pre_font, MAXCHAR);

	//	//CreateTextFormat(pre_font, size);
	//}

	//// ID2D1SolidColorBrushのラッパー
	//void D2DText::SetColor(const D2D1_COLOR_F & color)
	//{
	//	//CreateSolidBrush(color, SolidBrush);
	//}

	//// ID2D1SolidColorBrushのラッパー
	//void D2DText::SetOpacity(float alpha)
	//{
	//	//D2D1_COLOR_F pre_color = SolidBrush->GetColor();
	//	//CreateSolidBrush(pre_color, SolidBrush);
	//	//SolidBrush->SetOpacity(alpha);
	//}
#pragma endregion TextLine

#pragma region TextParam
	// クラス内static変数群
	// デフォルト描画順
	const int D2DTextParams::defDrawOrder = 100;


	D2DTextParams::D2DTextParams()
		: TextSetting(new TextData())
		, DrawOrder(defDrawOrder)
	{
		TextComponent = getEngine()->getD2DText();
		Manager = getEngine()->getD2DTextMng();
		Manager->Add(this);
	}

	//D2DTextParams::D2DTextParams(TextData * data, int drawOrder) : D2DTextParams()
	//{
	//	SetData(data);
	//	DrawOrder = drawOrder;
	//}

	//D2DTextParams::D2DTextParams(std::string str, D2D1_POINT_2F pos, D2D1_RECT_F rect,
	//	TextData::FORM form, int flag, FontData * data, int drawOrder) : D2DTextParams()
	//{
	//	TextSetting->Str = str;
	//	TextSetting->Pos = pos;
	//	TextSetting->Rect = rect;
	//	TextSetting->Form = form;
	//	TextSetting->DrawFlag = flag;
	//	TextSetting->Data = data;
	//	DrawOrder = drawOrder;
	//}
	
	D2DTextParams::~D2DTextParams()
	{
		Manager->Remove(this);
		Manager = nullptr;
		delete TextSetting->Data;	//下の命令で消える？よくわからん
		delete TextSetting;
		TextSetting = nullptr;
		TextComponent = nullptr;
	}

	void D2DTextParams::Draw()
	{
		if (TextSetting->DrawFlag == true) {
			TextComponent->SetFont(TextSetting->Data);
			switch (TextSetting->Form)
			{
			case F_lib_Render::TextData::FORM::Point:
				TextComponent->DrawString(TextSetting->Str, TextSetting->Pos);
				break;
			case F_lib_Render::TextData::FORM::Rect:
				TextComponent->DrawString(TextSetting->Str, TextSetting->Rect);
				break;
			default:
				break;
			}
		}
	}
	void D2DTextParams::SetData(TextData * data)
	{
		TextSetting->Str = data->Str;
		TextSetting->Pos = data->Pos;
		TextSetting->Rect = data->Rect;
		TextSetting->Form = data->Form;
		TextSetting->DrawFlag = data->DrawFlag;
		TextSetting->Data = data->Data;
	}
	void D2DTextParams::SetDrawOrder(int drawOrder)
	{
		Manager->ChangeDrawOrder(this, drawOrder);
		DrawOrder = drawOrder;
	}
#pragma endregion
}
