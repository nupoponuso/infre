#include "RenderTargetResources.h"


#define SAFE_RELEASE(x) if(x) {x->Release(); x=nullptr;}


namespace F_lib_Render
{
	// 利用するインターフェース
	ID2D1RenderTarget*	RenderTargetResources::RenderTarget = nullptr;
	// デフォルトブラシ
	ID2D1SolidColorBrush*	RenderTargetResources::BlackBrush = nullptr;
	ID2D1SolidColorBrush*	RenderTargetResources::BlueBrush = nullptr;
	ID2D1SolidColorBrush*	RenderTargetResources::GreenBrush = nullptr;
	ID2D1SolidColorBrush*	RenderTargetResources::RedBrush = nullptr;
	ID2D1LinearGradientBrush*		RenderTargetResources::GradientBrush = nullptr;
	ID2D1GradientStopCollection*	RenderTargetResources::GradientStops = nullptr;


	RenderTargetResources::RenderTargetResources()
	{
	}

	RenderTargetResources::~RenderTargetResources()
	{
	}

	HRESULT RenderTargetResources::Create(ID2D1RenderTarget * target)
	{
		HRESULT hr = S_OK;

		if (RenderTarget == nullptr) {
			RenderTarget = target;
			RenderTarget->AddRef();
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
		if (GradientBrush == nullptr) {
			static const D2D1_GRADIENT_STOP stops[] =
			{
				{   0.0f,  { 0.0f, 1.0f, 1.0f, 1.0f }  },
			{   1.0f,  { 0.0f, 0.0f, 1.0f, 0.5f }  },
			};
			hr = RenderTarget->CreateGradientStopCollection(
				stops, sizeof(stops) / sizeof(D2D1_GRADIENT_STOP), &GradientStops);
			if (FAILED(hr))
				return hr;
			hr = RenderTarget->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(
					D2D1::Point2F(100.0F, 120.0F),
					D2D1::Point2F(100.0F, 270.0F)),
				D2D1::BrushProperties(),
				GradientStops,
				&GradientBrush);
			if (FAILED(hr))
				return hr;
		}
		return hr;
	}

	void RenderTargetResources::DeleteResources()
	{
		SAFE_RELEASE(RenderTarget);
		SAFE_RELEASE(BlackBrush);
		SAFE_RELEASE(BlueBrush);
		SAFE_RELEASE(GreenBrush);
		SAFE_RELEASE(RedBrush);
		SAFE_RELEASE(GradientBrush);
		SAFE_RELEASE(GradientStops);
	}
}
