#pragma once

#include <vector>
#include <DirectXColors.h>
#include <d2d1.h>
#include <dwrite.h>

#include "RenderTargetResources.h"	// �����_�[�^�[�Q�b�g���\�[�X���܂Ƃ߂Ă���N���X

// lib�w��
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

//�O���錾
namespace F_lib_Render
{
class D2DTextMng;
}

namespace F_lib_Render
{
	class D2DText : public RenderTargetResources
	{
	protected:
		// ���p����C���^�[�t�F�[�X
		static IDWriteFactory*		DWriteFactory;
		// �f�t�H���g�t�H���g�p�����[�^
		static const WCHAR*			defFontFamiry;
		static const float			defFontSize;
		static D2D1_COLOR_F			defFontColor;
		static IDWriteTextFormat*	defTextFormat;
		// �f�t�H���g�`�揇
		static const int defDrawOrder;
		//// �`��Ǘ��N���X
		//static D2DTextMng* Manager;
		// static�Ŏ�����������肭�����Ȃ��̂ň�U�ʂ̕��@�Ŏ�������

	public:
		D2DText();
		D2DText(const std::wstring str, D2D1_RECT_F rect, int drawOrder = defDrawOrder);
		D2DText(const WCHAR* str, int length, D2D1_RECT_F rect, int drawOrder = defDrawOrder);
		~D2DText();
		
		// static�ϐ���������(���ꂼ��v���O��������1��ĂׂΗǂ�)
		// factory�̃|�C���^���擾(�K�{)
		static HRESULT Init(IDWriteFactory* factory, D2DTextMng* drawer);
		static void Uninit();

		// �����p�֐�(DWriteFactory���\�b�h�̃��b�p�[)
		HRESULT CreateTextFormat(const WCHAR* fontFamiyName, float fontSize);
		HRESULT CreateSolidBrush(D2D1_COLOR_F& c);
		

		//setter
		void SetText(std::wstring str);
		void SetText(WCHAR* str, int length);
		void SetRect(D2D1_RECT_F rect);
		void SetDrawFlag(bool enable);
		void SetFontSize(float size);
		void SetColor(D2D1_COLOR_F color);
		void SetOpacity(float alpha);

		// getter
		IDWriteFactory*			GetDWriteFactory() const { return DWriteFactory; }
		IDWriteTextFormat*		GetTextFormat() const { return TextFormat; }
		ID2D1SolidColorBrush*	GetSolidBrush() const { return SolidBrush; }
		const WCHAR*	GetText()		const { return Text; }
		int				GetTextLength()	const { return TextLength; }
		D2D1_RECT_F		GetDrawRect()	const { return DrawRect; }
		int				GetDrawOrder()	const { return DrawOrder; }
		bool			GetDrawFlag()	const { return DrawFlag; }
	private:
		// ���������o
		IDWriteTextFormat*		TextFormat;		// �e������͌ŗL�l��ێ�������̂Ƃ���
		ID2D1SolidColorBrush*	SolidBrush;		// �e������͌ŗL�l��ێ�������̂Ƃ���
		const WCHAR*	Text;		// �\��������
		int				TextLength;	// ������
		D2D1_RECT_F		DrawRect;	// �������`�悷�钷���`
		int				DrawOrder;	// ������̕`�揇���w�肷��(�傫���قǎ�O�\��)
		bool			DrawFlag;	// Drawer�ɕ`�悳���邩���w��(true:�`�悷��/false:���Ȃ�)
		D2DTextMng*		Manager;
	};
}
