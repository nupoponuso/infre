#include "RenderTargetResources.h"


namespace F_lib_Render
{
	// デフォルトブラシ
	ID2D1SolidColorBrush*	RenderTargetResources::BlackBrush = nullptr;
	ID2D1SolidColorBrush*	RenderTargetResources::BlueBrush  = nullptr;
	ID2D1SolidColorBrush*	RenderTargetResources::GreenBrush = nullptr;
	ID2D1SolidColorBrush*	RenderTargetResources::RedBrush   = nullptr;
	ID2D1LinearGradientBrush*		RenderTargetResources::GradientBrush = nullptr;
	ID2D1GradientStopCollection*	RenderTargetResources::GradientStops = nullptr;


	RenderTargetResources::RenderTargetResources(ID2D1RenderTarget* target)
		: RenderTarget(nullptr)
	{
		InitAndCreate(target);
	}

	RenderTargetResources::~RenderTargetResources()
	{
		DeleteResources();
	}

	HRESULT RenderTargetResources::InitAndCreate(ID2D1RenderTarget * target)
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
		else {
			BlackBrush->AddRef();
		}
		if (BlueBrush == nullptr) {
			hr = RenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0F, 0.0F, 1.0F, 1.0F), &BlueBrush);
			if (FAILED(hr)) return hr;
		} else {
			BlueBrush->AddRef();
		}
		if (GreenBrush == nullptr) {
			hr = RenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0F, 1.0F, 0.0F, 1.0F), &GreenBrush);
			if (FAILED(hr)) return hr;
		} else {
			GreenBrush->AddRef();
		}
		if (RedBrush == nullptr) {
			hr = RenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0F, 0.0F, 0.0F, 1.0F), &RedBrush);
			if (FAILED(hr)) return hr;
		} else {
			RedBrush->AddRef();
		}
		if (GradientBrush == nullptr) {
			static const D2D1_GRADIENT_STOP stops[] =	// 色の変化を指定
			{
				{   0.0f,  { 0.0f, 1.0f, 1.0f, 1.0f }  },	// 開始座標,色
				{   1.0f,  { 0.0f, 0.0f, 1.0f, 0.5f }  },	// 終了座標,色
			};
			hr = RenderTarget->CreateGradientStopCollection(
				stops, sizeof(stops) / sizeof(D2D1_GRADIENT_STOP), &GradientStops);
			if (FAILED(hr))
				return hr;
			hr = RenderTarget->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(
					D2D1::Point2F(100.0F, 120.0F),	// 開始点
					D2D1::Point2F(100.0F, 270.0F)),	// 終了点
				D2D1::BrushProperties(),
				GradientStops,
				&GradientBrush);
			if (FAILED(hr))
				return hr;
		} else {
			GradientBrush->AddRef();
			GradientStops->AddRef();
		}

		return hr;
	}

	void RenderTargetResources::DeleteResources()
	{
		SAFE_RELEASE(RenderTarget);
		STATIC_SAFE_RELEASE(BlackBrush);
		STATIC_SAFE_RELEASE(BlueBrush);
		STATIC_SAFE_RELEASE(GreenBrush);
		STATIC_SAFE_RELEASE(RedBrush);
		STATIC_SAFE_RELEASE(GradientBrush);
		STATIC_SAFE_RELEASE(GradientStops);
	}

	HRESULT RenderTargetResources::CreateSolidBrush(const D2D1_COLOR_F & color, ID2D1SolidColorBrush * brush)
	{
		HRESULT hr = S_OK;

		hr = RenderTarget->CreateSolidColorBrush(color, &brush);
		if (FAILED(hr))
			return hr;

		return hr;
	}
}
