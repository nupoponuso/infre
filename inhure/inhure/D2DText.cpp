#include "D2DText.h"

#include <assert.h>

#define SAFE_RELEASE(x) if(x) {x->Release(); x=nullptr;}


namespace F_lib_Render
{
	// �N���X��static�ϐ��Q
	// ���p����C���^�[�t�F�[�X
	IDWriteFactory*		D2DText::DWriteFactory = nullptr;
	ID2D1RenderTarget*	D2DText::RenderTarget = nullptr;
	// �f�t�H���g�t�H���g�p�����[�^
	const WCHAR*		D2DText::defFontFamiry	= L"���C���I";
	const float			D2DText::defFontSize	= 20.0f;
	D2D1_COLOR_F		D2DText::defFontColor	= { 1.0F, 1.0F, 1.0F, 1.0F };
	IDWriteTextFormat*	D2DText::defTextFormat	= nullptr;
	// �f�t�H���g�u���V
	ID2D1SolidColorBrush*	D2DText::BlackBrush = nullptr;
	ID2D1SolidColorBrush*	D2DText::BlueBrush  = nullptr;
	ID2D1SolidColorBrush*	D2DText::GreenBrush = nullptr;
	ID2D1SolidColorBrush*	D2DText::RedBrush   = nullptr;
	// Init�ς�Flag
	bool D2DText::InitedFlag = false;		// true:�ς�/false:��������
	// �f�t�H���g�`�揇
	const int D2DText::defDrawOrder = 100;

#pragma region D2DTextInitialize
HRESULT D2DText::InitText(IDWriteFactory* factory, ID2D1RenderTarget* target)
{
	HRESULT hr = S_OK;

	if (InitedFlag == false) {
		// �K�{�C���^�[�t�F�[�X�̃|�C���^���擾
		if (factory == nullptr) hr = E_FAIL;
		DWriteFactory = factory;
		if (target == nullptr) hr = E_FAIL;
		RenderTarget = target;

		DWriteFactory->AddRef();
		RenderTarget->AddRef();
		InitedFlag = true;

		if (defTextFormat == nullptr) {
			DWriteFactory->CreateTextFormat(
				defFontFamiry,
				nullptr,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				defFontSize,
				L"",
				&defTextFormat
			);
			defTextFormat->AddRef();
		}
		if (BlackBrush == nullptr) {
			hr = RenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0F, 1.0F, 1.0F, 1.0F), &BlackBrush);
			if (FAILED(hr)) return hr;
		}
		if (BlueBrush == nullptr) {
			hr = RenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0F, 0.0F, 1.0F, 1.0F), &BlueBrush);
			if (FAILED(hr)) return hr;
		}
		if (GreenBrush == nullptr) {
			hr = RenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0F, 1.0F, 0.0F, 1.0F), &GreenBrush);
			if (FAILED(hr)) return hr;
		}
		if (RedBrush == nullptr) {
			hr = RenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0F, 0.0F, 0.0F, 1.0F), &RedBrush);
			if (FAILED(hr)) return hr;
		}
	} else {
		// �Ȃɂ����Ȃ�
	}

	return hr;
}

void D2DText::UninitText()
{
	if (InitedFlag == true) {
		SAFE_RELEASE(DWriteFactory);
		SAFE_RELEASE(RenderTarget);
		SAFE_RELEASE(defTextFormat);
		SAFE_RELEASE(BlackBrush);
		SAFE_RELEASE(BlueBrush);
		SAFE_RELEASE(GreenBrush);
		SAFE_RELEASE(RedBrush);
		InitedFlag = false;
	} else {
		// �Ȃɂ����Ȃ�
	}
}
#pragma endregion D2DTextInitialize




#pragma region TextLine
	D2DText::D2DText()
		: Text(nullptr)
		, TextLength(0)
		, DrawRect(D2D1_RECT_F{ 0,0,10.0f,10.0f })
		, DrawOrder(defDrawOrder)
	{
		assert(InitedFlag == true);	// IniteText()����x���Ă΂�Ă��Ȃ��ƃG���[

		//DWriteFactory = DWriteFactory;
		//RenderTarget = RenderTarget;
		TextFormat = defTextFormat;
		SolidBrush = BlackBrush;
		
		DWriteFactory->AddRef();
		RenderTarget->AddRef();
		TextFormat->AddRef();
		SolidBrush->AddRef();
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
		SAFE_RELEASE(DWriteFactory);
		SAFE_RELEASE(RenderTarget);
		SAFE_RELEASE(TextFormat);
		SAFE_RELEASE(SolidBrush);
	}

	HRESULT D2DText::CreateTextFormat(const WCHAR * fontFamiyName, float fontSize)
	{
		HRESULT hr = S_OK;
		
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
		TextFormat->AddRef();
		return hr;
	}

	HRESULT D2DText::CreateSolidBrush(D2D1_COLOR_F & c)
	{
		HRESULT hr = S_OK;

		SAFE_RELEASE(SolidBrush);

		hr = RenderTarget->CreateSolidColorBrush(c, &SolidBrush);
		if (FAILED(hr))
			return hr;
		SolidBrush->AddRef();
		return hr;
	}

	void D2DText::SetText(const std::wstring str)
	{
		Text = str.c_str();
	}

	void D2DText::SetText(const WCHAR * str, int length)
	{
		Text = str;
		TextLength = length;
	}

	void D2DText::SetRect(D2D1_RECT_F rect)
	{
		DrawRect = rect;
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
