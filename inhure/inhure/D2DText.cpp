#include "D2DText.h"

#include "D2DDrawMng.h"

#include "RenderingEngine.h"

#define SAFE_RELEASE(x) if(x) {x->Release(); x=nullptr;}


namespace F_lib_Render
{
	// クラス内static変数群
	// 利用するインターフェース
	IDWriteFactory*		D2DText::DWriteFactory = nullptr;
	// デフォルトフォントパラメータ
	const WCHAR*		D2DText::defFontFamiry	= L"メイリオ";
	const float			D2DText::defFontSize	= 20.0f;
	D2D1_COLOR_F		D2DText::defFontColor	= { 1.0F, 1.0F, 1.0F, 1.0F };
	IDWriteTextFormat*	D2DText::defTextFormat	= nullptr;
	// デフォルト描画順
	const int D2DText::defDrawOrder = 100;
	// 描画管理クラス
	//D2DTextMng* Manager = nullptr;

#pragma region D2DTextInitialize
HRESULT D2DText::Init(IDWriteFactory* factory, D2DTextMng* drawer)
{
	HRESULT hr = S_OK;

	// 必須インターフェースのポインタを取得
	if (DWriteFactory == nullptr) {
		DWriteFactory = factory;
		DWriteFactory->AddRef();
	}

	if (defTextFormat == nullptr) {
		hr = DWriteFactory->CreateTextFormat(
			defFontFamiry,
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			defFontSize,
			L"",
			&defTextFormat
		);
		if (FAILED(hr))
			return hr;
	}

	//if (Manager == nullptr) {
	//	Manager = drawer;
	//}

	return hr;
}

void D2DText::Uninit()
{
	SAFE_RELEASE(DWriteFactory);
	SAFE_RELEASE(defTextFormat);
	//Manager = nullptr;
}
#pragma endregion D2DTextInitialize




#pragma region TextLine
	D2DText::D2DText()
		: RenderTargetResources()
		, Text(nullptr)
		, TextLength(0)
		, DrawRect(D2D1_RECT_F{ 0,0,10.0f,10.0f })
		, DrawOrder(defDrawOrder)
		, DrawFlag(true)
	{
		if (DWriteFactory) {
			DWriteFactory->AddRef();
		}
		if (defTextFormat) {
			TextFormat = defTextFormat;
			TextFormat->AddRef();
		}
		if (BlackBrush) {
			SolidBrush = BlackBrush;
			SolidBrush->AddRef();
		}

		// 生成したら即登録
		//if (Manager) {
		//	Manager->Add(this);
		//}
		Manager = getEngine()->getD2DTextMng();
		Manager->Add(this);
	}

	D2DText::D2DText(const std::wstring str, D2D1_RECT_F rect, int drawOrder) : D2DText()
	{
		// 委譲コンストラクタで一旦初期化、必要な箇所のみ更新
		Text = str.c_str();
		TextLength = static_cast<int>(str.size());
		DrawRect = rect;
		DrawOrder = drawOrder;
	}

	D2DText::D2DText(const WCHAR* str, int length, D2D1_RECT_F rect, int drawOrder) : D2DText()
	{
		// 委譲コンストラクタで一旦初期化、必要な箇所のみ更新
		Text = str;
		TextLength = length;
		DrawRect = rect;
		DrawOrder = drawOrder;
	}

	D2DText::~D2DText()
	{
		Manager->Remove(this);
		SAFE_RELEASE(DWriteFactory);
		SAFE_RELEASE(TextFormat);
		SAFE_RELEASE(SolidBrush);
	}

	HRESULT D2DText::CreateTextFormat(const WCHAR * fontFamiyName, float fontSize)
	{
		HRESULT hr = S_OK;
		
		// Init()で設定し忘れていた場合はエラー
		if (DWriteFactory == nullptr) {
			return E_POINTER;
		}

		// 利用しているデフォルトブラシの参照カウンタを減らすor現状のリソース解放
		SAFE_RELEASE(TextFormat);

		 hr = DWriteFactory->CreateTextFormat(
			fontFamiyName,
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize,
			L"",
			&TextFormat
		);
		 if (FAILED(hr))
			 return hr;

		TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

		return hr;
	}

	HRESULT D2DText::CreateSolidBrush(D2D1_COLOR_F & c)
	{
		HRESULT hr = S_OK;

		// 利用しているデフォルトブラシの参照カウンタを減らすor現状のリソース解放
		SAFE_RELEASE(SolidBrush);

		//Init()で設定し忘れていた場合はエラー
		if (RenderTarget == nullptr) {
			return E_POINTER;
		}

		hr = RenderTarget->CreateSolidColorBrush(c, &SolidBrush);
		if (FAILED(hr))
			return hr;

		return hr;
	}

	void D2DText::SetText(std::wstring str)
	{
		Text = const_cast<WCHAR*>(str.c_str());
	}

	void D2DText::SetText(WCHAR * str, int length)
	{
		Text = str;
		TextLength = length;
	}

	void D2DText::SetRect(D2D1_RECT_F rect)
	{
		DrawRect = rect;
	}

	void D2DText::SetDrawFlag(bool enable)
	{
		DrawFlag = enable;
	}

	void D2DText::SetFontSize(float size)
	{
		WCHAR pre_font[32];
		TextFormat->GetFontFamilyName(pre_font, 32);

		CreateTextFormat(pre_font, size);
	}

	// ID2D1SolidColorBrushのラッパー
	void D2DText::SetColor(D2D1_COLOR_F color)
	{
		SolidBrush->SetColor(color);
	}

	// ID2D1SolidColorBrushのラッパー
	void D2DText::SetOpacity(float alpha)
	{
		SolidBrush->SetOpacity(alpha);
	}
#pragma endregion TextLine
}
