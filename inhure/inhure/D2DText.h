#pragma once

#include <vector>
#include <DirectXColors.h>
#include <d2d1.h>
#include <dwrite.h>

// lib�w��
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")


namespace F_lib_Render
{
	class D2DText
	{
	protected:
		// ���p����C���^�[�t�F�[�X
		static IDWriteFactory*		DWriteFactory;
		static ID2D1RenderTarget*	RenderTarget;
		// �f�t�H���g�t�H���g�p�����[�^
		static const WCHAR*			defFontFamiry;
		static const float			defFontSize;
		static D2D1_COLOR_F			defFontColor;
		static IDWriteTextFormat*	defTextFormat;
		// �f�t�H���g�u���V
		static ID2D1SolidColorBrush*	BlackBrush;
		static ID2D1SolidColorBrush*	BlueBrush;
		static ID2D1SolidColorBrush*	GreenBrush;
		static ID2D1SolidColorBrush*	RedBrush;
		// Init�ς�Flag
		static bool InitedFlag;		// true:�ς�/false:��������
		// �f�t�H���g�`�揇
		static const int defDrawOrder;

	public:
		D2DText();
		D2DText(const std::wstring str, D2D1_RECT_F rect, int drawOrder = defDrawOrder);
		D2DText(const WCHAR* str, int length, D2D1_RECT_F rect, int drawOrder = defDrawOrder);
		~D2DText();
		
		// static�ϐ���������(���ꂼ��v���O��������1��ĂׂΗǂ�)
		// factory, rendertarget�̃|�C���^���擾(�K�{)
		static HRESULT InitText(IDWriteFactory* factory, ID2D1RenderTarget* target);
		static void UninitText();

		// �����p�֐�(DWriteFactory���\�b�h�̃��b�p�[)
		HRESULT CreateTextFormat(const WCHAR* fontFamiyName, float fontSize);
		HRESULT CreateSolidBrush(D2D1_COLOR_F& c);
		

		//setter
		void SetText(const std::wstring str);
		void SetText(const WCHAR* str, int length);
		void SetRect(D2D1_RECT_F rect);
		void SetFontSize(float size);
		void SetColor(D2D1_COLOR_F color);
		void SetOpacity(float alpha);

		// getter
		IDWriteFactory*			GetDWriteFactory() const { return DWriteFactory; }
		ID2D1RenderTarget*		GetRenderTarget() const { return RenderTarget; }
		IDWriteTextFormat*		GetTextFormat() const { return TextFormat; }
		ID2D1SolidColorBrush*	GetSolidBrush() const { return SolidBrush; }
		const WCHAR*	GetText()		const { return Text; }
		int				GetTextSize()	const { return TextLength; }
		D2D1_RECT_F		GetDrawRect()	const { return DrawRect; }
		int				GetDrawOrder()	const { return DrawOrder; }
	private:
		// ���������o
		IDWriteTextFormat*		TextFormat;		// �e������͌ŗL�l��ێ�������̂Ƃ���
		ID2D1SolidColorBrush*	SolidBrush;		// �e������͌ŗL�l��ێ�������̂Ƃ���
		const WCHAR*	Text;		// �\��������
		int				TextLength;	// ������
		D2D1_RECT_F		DrawRect;	// �������`�悷�钷���`
		int				DrawOrder;	// ������̕`�揇���w�肷��(�傫���قǎ�O�\��) 
	};
}
