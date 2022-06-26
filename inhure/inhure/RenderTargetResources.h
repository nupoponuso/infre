#pragma once

// インクルード
#include <d2d1.h>
#include <dwrite.h>

// lib指定
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

//マクロ
#define SAFE_RELEASE(x) if(x) {x->Release(); x=nullptr;}
#define STATIC_SAFE_RELEASE(x)	if(x) {int cnt = x->Release(); if(cnt==0) {x=nullptr;}}

namespace F_lib_Render
{
	class RenderTargetResources
	{
	protected:
		// デフォルトブラシ
		// 名称指定で利用できる
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
		//Init,Uninit用ヘルパー
		HRESULT InitAndCreate(ID2D1RenderTarget* target);
		void DeleteResources();

	public:
		// 標準関数のラッパー
		// SolidBrush以外の標準関数は都度、RenderTargetから作成すること
		/* @brief  ブラシリソースの作成
		* @param[in]	color	色指定
		* @param[out]	brush	保存先ポインタ
		* @return		HRESUTL	処理結果
		*/
		HRESULT CreateSolidBrush(const D2D1_COLOR_F& color, ID2D1SolidColorBrush* brush);
		
		//getter
		ID2D1RenderTarget* GetRenderTarget() const { return RenderTarget; }

	protected:
		ID2D1RenderTarget*	RenderTarget;	// 利用するインターフェース
	};
}