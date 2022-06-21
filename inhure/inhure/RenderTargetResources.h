#pragma once

// インクルード
#include <d2d1.h>
#include <dwrite.h>

// lib指定
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

namespace F_lib_Render
{
	class RenderTargetResources
	{
	protected:
		// 利用するインターフェース
		static ID2D1RenderTarget*	RenderTarget;
		// デフォルトブラシ
		static ID2D1SolidColorBrush*	BlackBrush;
		static ID2D1SolidColorBrush*	BlueBrush;
		static ID2D1SolidColorBrush*	GreenBrush;
		static ID2D1SolidColorBrush*	RedBrush;
		static ID2D1LinearGradientBrush*	GradientBrush;
		static ID2D1GradientStopCollection* GradientStops;

	protected:
		RenderTargetResources();
		virtual ~RenderTargetResources();

	public:
		static HRESULT Create(ID2D1RenderTarget* target);
		static void DeleteResources();

		ID2D1RenderTarget* GetRenderTarget() const { return RenderTarget; }
	};
}