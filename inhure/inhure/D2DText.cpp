#include "D2DText.h"

#include "D2DDrawMng.h"

#include "RenderingEngine.h"

#define SAFE_RELEASE(x) if(x) {x->Release(); x=nullptr;}


namespace F_lib_Render
{
	// �N���X��static�ϐ��Q
	// ���p����C���^�[�t�F�[�X
	IDWriteFactory*		D2DText::DWriteFactory = nullptr;
	// �f�t�H���g�t�H���g�p�����[�^
	const WCHAR*		D2DText::defFontFamiry	= L"���C���I";
	const float			D2DText::defFontSize	= 20.0f;
	D2D1_COLOR_F		D2DText::defFontColor	= { 1.0F, 1.0F, 1.0F, 1.0F };
	IDWriteTextFormat*	D2DText::defTextFormat	= nullptr;
	// �f�t�H���g�`�揇
	const int D2DText::defDrawOrder = 100;
	// �`��Ǘ��N���X
	//D2DTextMng* Manager = nullptr;

#pragma region D2DTextInitialize
HRESULT D2DText::Init(IDWriteFactory* factory, D2DTextMng* drawer)
{
	HRESULT hr = S_OK;

	// �K�{�C���^�[�t�F�[�X�̃|�C���^���擾
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

		// ���������瑦�o�^
		//if (Manager) {
		//	Manager->Add(this);
		//}
		Manager = getEngine()->getD2DTextMng();
		Manager->Add(this);
	}

	D2DText::D2DText(const std::wstring str, D2D1_RECT_F rect, int drawOrder) : D2DText()
	{
		// �Ϗ��R���X�g���N�^�ň�U�������A�K�v�ȉӏ��̂ݍX�V
		Text = str.c_str();
		TextLength = static_cast<int>(str.size());
		DrawRect = rect;
		DrawOrder = drawOrder;
	}

	D2DText::D2DText(const WCHAR* str, int length, D2D1_RECT_F rect, int drawOrder) : D2DText()
	{
		// �Ϗ��R���X�g���N�^�ň�U�������A�K�v�ȉӏ��̂ݍX�V
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
		
		// Init()�Őݒ肵�Y��Ă����ꍇ�̓G���[
		if (DWriteFactory == nullptr) {
			return E_POINTER;
		}

		// ���p���Ă���f�t�H���g�u���V�̎Q�ƃJ�E���^�����炷or����̃��\�[�X���
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

		// ���p���Ă���f�t�H���g�u���V�̎Q�ƃJ�E���^�����炷or����̃��\�[�X���
		SAFE_RELEASE(SolidBrush);

		//Init()�Őݒ肵�Y��Ă����ꍇ�̓G���[
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

	// ID2D1SolidColorBrush�̃��b�p�[
	void D2DText::SetColor(D2D1_COLOR_F color)
	{
		SolidBrush->SetColor(color);
	}

	// ID2D1SolidColorBrush�̃��b�p�[
	void D2DText::SetOpacity(float alpha)
	{
		SolidBrush->SetOpacity(alpha);
	}
#pragma endregion TextLine
}
