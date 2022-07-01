#pragma once

// �C���N���[�h
#include <d2d1.h>
#include <dwrite.h>

// lib�w��
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

//�}�N��
#define SAFE_RELEASE(x) if(x) {x->Release(); x=nullptr;}
#define STATIC_SAFE_RELEASE(x)	if(x) {int cnt = x->Release(); if(cnt==0) {x=nullptr;}}

namespace F_lib_Render
{
	class RenderTargetResources
	{
	protected:
		// �f�t�H���g�u���V
		// ���̎w��ŗ��p�ł���
		static ID2D1SolidColorBrush*	BlackBrush;
		static ID2D1SolidColorBrush*	BlueBrush;
		static ID2D1SolidColorBrush*	GreenBrush;
		static ID2D1SolidColorBrush*	RedBrush;
		static ID2D1LinearGradientBrush*	GradientBrush;
		static ID2D1GradientStopCollection* GradientStops;

	protected:
		RenderTargetResources(ID2D1RenderTarget* target);
		virtual ~RenderTargetResources();

	private:
		//Init,Uninit�p�w���p�[
		HRESULT InitAndCreate(ID2D1RenderTarget* target);
		void DeleteResources();

	public:
		// �W���֐��̃��b�p�[
		// SolidBrush�ȊO�̕W���֐��͓s�x�ARenderTarget����쐬���邱��
		/* @brief  �u���V���\�[�X�̍쐬
		* @param[in]	color	�F�w��
		* @param[out]	brush	�ۑ���|�C���^
		* @return		HRESUTL	��������
		*/
		HRESULT CreateSolidBrush(const D2D1_COLOR_F& color, ID2D1SolidColorBrush* brush);
		
		//getter
		ID2D1RenderTarget* GetRenderTarget() const { return RenderTarget; }

	protected:
		ID2D1RenderTarget*	RenderTarget;	// ���p����C���^�[�t�F�[�X
	};
}