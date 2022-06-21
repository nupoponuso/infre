#include "D2DFunctions.h"

#include <assert.h>	// 今はassertにしているが、例外処理の方が適しているかもしれない

#define SAFE_RELEASE(x) if(x) {x->Release(); x=nullptr;}


namespace D2DFunctions
{
	// staticメンバーの初期化
	//F_lib_Render::RenderingEngine* Engine = nullptr;
	// 利用するインターフェース
	ID2D1Factory*			D2DFuncComponent::D2DFactory   = nullptr;
	ID2D1RenderTarget*		D2DFuncComponent::RenderTarget = nullptr;
	// デフォルトブラシ
	ID2D1SolidColorBrush*	D2DFuncComponent::BlackBrush   = nullptr;
	ID2D1SolidColorBrush*	D2DFuncComponent::BlueBrush    = nullptr;
	ID2D1SolidColorBrush*	D2DFuncComponent::GreenBrush   = nullptr;
	ID2D1SolidColorBrush*	D2DFuncComponent::RedBrush     = nullptr;
	// Init済みFlag
	bool D2DFuncComponent::InitedFlag = false;
	// デフォルト描画順
	const int D2DFuncComponent::defDrawOrder = 100;


#pragma region D2DFuncInitialize
	HRESULT D2DFuncComponent::InitD2DFunc(ID2D1Factory * factory, ID2D1RenderTarget * target)
	{
		HRESULT hr = S_OK;

		if (InitedFlag == false) {	// static変数が初期化されていなかったら処理する
			if (factory == nullptr) hr = E_FAIL;
			D2DFactory = factory;
			if (target == nullptr) hr = E_FAIL;
			RenderTarget = target;

			D2DFactory->AddRef();
			RenderTarget->AddRef();
			InitedFlag = true;

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
			//何もしない
		}

		return hr;
	}

	void D2DFuncComponent::UninitD2DFunc()
	{
		if (InitedFlag == true) {
			SAFE_RELEASE(D2DFactory);
			SAFE_RELEASE(RenderTarget);
			SAFE_RELEASE(BlackBrush);
			SAFE_RELEASE(BlueBrush);
			SAFE_RELEASE(GreenBrush);
			SAFE_RELEASE(RedBrush);
			InitedFlag = false;
		} else {
			// なにもしない
		}
	}
	void D2DFuncComponent::Draw()
	{
	}
#pragma endregion D2DFuncInitialize


#pragma region D2DFuncBase
	D2DFuncComponent::D2DFuncComponent()
		:DrawOrder(defDrawOrder)
	{
		assert(InitedFlag == true);	//Init()済みでなければならない
	}

	D2DFuncComponent::~D2DFuncComponent()
	{
	}
	
#pragma endregion D2DFuncBase



#pragma region D2DInheritance
	D2DGauge::D2DGauge()
	{
		// 何もしない
	}
	D2DGauge::~D2DGauge()
	{
		// 何もしない
	}
	void D2DGauge::Draw()
	{
		DrawCircleGauge();
	}
#pragma region D2DGaugeDrawer
	void D2DGauge::DrawCircleGauge()
	{
		//円の描画  
		D2D1_ELLIPSE ellipse1 = D2D1::Ellipse(D2D1::Point2F(120.0F, 120.0F), 100.0F, 100.0F);
		RenderTarget->DrawEllipse(ellipse1, GreenBrush, 10.0F);
	}
	void D2DGauge::DrawRoundRectangle()
	{
		//四角の描画  
		D2D1_RECT_F rect1 = D2D1::RectF(100.0F, 50.0F, 300.0F, 100.F);
		RenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(rect1, 10.0f, 10.0f), BlueBrush);
	}
	HRESULT D2DGauge::DrawArc(ID2D1PathGeometry * pGeometry, D2D_POINT_2F ptCenterF, FLOAT fRotationAngle, FLOAT fSweepAngle, FLOAT fRadius, D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd)
	{
		ID2D1GeometrySink *pSink = NULL;

		HRESULT hr = S_FALSE;

		D2D_POINT_2F ptStartF = { 0.0f, 0.0f };
		D2D_POINT_2F ptEndF = { 0.0f, 0.0f };

		ptStartF = CalcCartesianCoordinate(fRotationAngle, fRadius);
		ptStartF.x += ptCenterF.x;
		ptStartF.y += ptCenterF.y;

		ptEndF = CalcCartesianCoordinate(fRotationAngle + fSweepAngle, fRadius);
		ptEndF.x += ptCenterF.x;
		ptEndF.y += ptCenterF.y;

		hr = pGeometry->Open(&pSink);
		if (SUCCEEDED(hr)) {
			pSink->SetFillMode(fillMode);

			pSink->BeginFigure(ptCenterF, figureBegin);
			pSink->AddLine(ptStartF);
			pSink->AddArc(
				D2D1::ArcSegment(
					ptEndF,
					D2D1::SizeF(fRadius, fRadius),
					0.0f, // rotation angle
					D2D1_SWEEP_DIRECTION_CLOCKWISE,
					(fSweepAngle > 180.0f) ? D2D1_ARC_SIZE_LARGE : D2D1_ARC_SIZE_SMALL
				));
			pSink->EndFigure(figureEnd);

			hr = pSink->Close();
			if (SUCCEEDED(hr))
				SAFE_RELEASE(pSink);
		}
		return hr;
	}
	HRESULT D2DGauge::DrawPie(ID2D1PathGeometry * pGeometry, D2D_POINT_2F ptCenterF, FLOAT fRotationAngle, FLOAT fSweepAngle, FLOAT fOuterRadius, FLOAT fInnerRadius, D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd)
	{
		ID2D1GeometrySink *pSink = NULL;

		HRESULT hr = S_FALSE;

		D2D_POINT_2F ptInStartF = { 0.0f, 0.0f };
		D2D_POINT_2F ptInEndF = { 0.0f, 0.0f };

		D2D_POINT_2F ptOutStartF = { 0.0f, 0.0f };
		D2D_POINT_2F ptOutEndF = { 0.0f, 0.0f };

		ptInStartF = CalcCartesianCoordinate(fRotationAngle, fInnerRadius);
		ptInStartF.x += ptCenterF.x;
		ptInStartF.y += ptCenterF.y;

		ptInEndF = CalcCartesianCoordinate(fRotationAngle + fSweepAngle, fInnerRadius);
		ptInEndF.x += ptCenterF.x;
		ptInEndF.y += ptCenterF.y;

		ptOutStartF = CalcCartesianCoordinate(fRotationAngle, fOuterRadius);
		ptOutStartF.x += ptCenterF.x;
		ptOutStartF.y += ptCenterF.y;

		ptOutEndF = CalcCartesianCoordinate(fRotationAngle + fSweepAngle, fOuterRadius);
		ptOutEndF.x += ptCenterF.x;
		ptOutEndF.y += ptCenterF.y;


		hr = pGeometry->Open(&pSink);

		if (SUCCEEDED(hr)) {
			pSink->SetFillMode(fillMode);
			pSink->BeginFigure(ptInStartF, figureBegin);
			pSink->AddLine(ptOutStartF);
			pSink->AddArc(
				D2D1::ArcSegment(
					ptOutEndF,
					D2D1::SizeF(fOuterRadius, fOuterRadius),
					0.0f, // rotation angle
					D2D1_SWEEP_DIRECTION_CLOCKWISE,
					(fSweepAngle > 180.0f) ? D2D1_ARC_SIZE_LARGE : D2D1_ARC_SIZE_SMALL
				));
			pSink->AddLine(ptInEndF);
			pSink->AddArc(
				D2D1::ArcSegment(
					ptInStartF,
					D2D1::SizeF(fInnerRadius, fInnerRadius),
					0.0f, // rotation angle
					D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE,
					(fSweepAngle > 180.0f) ? D2D1_ARC_SIZE_LARGE : D2D1_ARC_SIZE_SMALL
				));
			pSink->EndFigure(figureEnd);

			hr = pSink->Close();

			if (SUCCEEDED(hr))
				SAFE_RELEASE(pSink);
		}
		return hr;
	}
#pragma endregion D2DGaugeDrawer

#pragma region D2DGaugeHelper
	//HRESULT D2DGauge::CreateResources(ID2D1RenderTarget * rt)
	//{
	//	HRESULT hr = S_OK;
	//	if (rt == nullptr) {
	//		return E_FAIL;
	//	}

	//	if (BlackBrush == nullptr) {
	//		hr = rt->CreateSolidColorBrush(D2D1::ColorF(1.0F, 1.0F, 1.0F, 1.0F), &BlackBrush);
	//		if (FAILED(hr)) return hr;
	//	}
	//	if (BlueBrush == nullptr) {
	//		hr = rt->CreateSolidColorBrush(D2D1::ColorF(0.0F, 0.0F, 1.0F, 1.0F), &BlueBrush);
	//		if (FAILED(hr)) return hr;
	//	}
	//	if (GreenBrush == nullptr) {
	//		hr = rt->CreateSolidColorBrush(D2D1::ColorF(0.0F, 1.0F, 0.0F, 1.0F), &GreenBrush);
	//		if (FAILED(hr)) return hr;
	//	}
	//	if (RedBrush == nullptr) {
	//		hr = rt->CreateSolidColorBrush(D2D1::ColorF(1.0F, 0.0F, 0.0F, 1.0F), &RedBrush);
	//		if (FAILED(hr)) return hr;
	//	}
	//	return hr;
	//}
	//void D2DGauge::DeleteResources()
	//{
	//	SAFE_RELEASE(D2DFactory);
	//	SAFE_RELEASE(RenderTarget);

	//	SAFE_RELEASE(BlackBrush);
	//	SAFE_RELEASE(BlueBrush);
	//	SAFE_RELEASE(GreenBrush);
	//	SAFE_RELEASE(RedBrush);
	//}

	D2D_POINT_2F D2DGauge::CalcCartesianCoordinate(FLOAT fAngle, FLOAT fRadius)
	{
		double dblAngleRad = 0.0f;
		FLOAT x = 0.0f, y = 0.0f;

		dblAngleRad = (M_PI / 180.0f) * (fAngle - 90.0f);

		x = (FLOAT)(fRadius * cos(dblAngleRad));
		y = (FLOAT)(fRadius * sin(dblAngleRad));
		return D2D1::Point2F(x, y);
	}
#pragma endregion D2DGaugeHelper
#pragma endregion D2DInheritance
}


//// プロトタイプ宣言
//HRESULT CreateResources(ID2D1RenderTarget* rt);
//void DeleteResources();
//
//// 無名名前空間：このcppのみで有効なグローバル変数
//namespace
//{	// Resources
//	// 利用するインターフェース
//	ID2D1Factory*			D2DFactory = nullptr;
//	ID2D1RenderTarget*		RenderTarget = nullptr;
//
//	// デフォルトブラシ
//	ID2D1SolidColorBrush*	BlackBrush = nullptr;
//	ID2D1SolidColorBrush*	BlueBrush = nullptr;
//	ID2D1SolidColorBrush*	GreenBrush = nullptr;
//	ID2D1SolidColorBrush*	RedBrush = nullptr;
//}
//
//#pragma region D2DFuncResources
//HRESULT CreateResources(ID2D1RenderTarget * rt)
//{
//	HRESULT hr = S_OK;
//	if (rt == nullptr) {
//		return E_FAIL;
//	}
//
//	if (BlackBrush == nullptr) {
//		hr = rt->CreateSolidColorBrush(D2D1::ColorF(1.0F, 1.0F, 1.0F, 1.0F), &BlackBrush);
//		if (FAILED(hr)) return hr;
//	}
//	if (BlueBrush == nullptr) {
//		hr = rt->CreateSolidColorBrush(D2D1::ColorF(0.0F, 0.0F, 1.0F, 1.0F), &BlueBrush);
//		if (FAILED(hr)) return hr;
//	}
//	if (GreenBrush == nullptr) {
//		hr = rt->CreateSolidColorBrush(D2D1::ColorF(0.0F, 1.0F, 0.0F, 1.0F), &GreenBrush);
//		if (FAILED(hr)) return hr;
//	}
//	if (RedBrush == nullptr) {
//		hr = rt->CreateSolidColorBrush(D2D1::ColorF(1.0F, 0.0F, 0.0F, 1.0F), &RedBrush);
//		if (FAILED(hr)) return hr;
//	}
//	return hr;
//}
//
//void DeleteResources()
//{
//	SAFE_RELEASE(D2DFactory);
//	SAFE_RELEASE(RenderTarget);
//
//	SAFE_RELEASE(BlackBrush);
//	SAFE_RELEASE(BlueBrush);
//	SAFE_RELEASE(GreenBrush);
//	SAFE_RELEASE(RedBrush);
//}
//#pragma endregion D2DFuncResources
//
//
//#pragma region D2DFunctions
//#pragma region D2DFuncInit
//void D2DFunctions::InitD2DFunctions(ID2D1Factory* factory, ID2D1RenderTarget * render_target)
//{
//	D2DFactory = factory;
//	RenderTarget = render_target;
//	 
//	D2DFactory->AddRef();
//	RenderTarget->AddRef();
//
//	if (RenderTarget) {
//		CreateResources(render_target);
//	}
//}
//
//void D2DFunctions::UninitD2DFunctions()
//{
//	DeleteResources();
//}
//#pragma endregion D2DFuncInit
//
//#pragma region D2DFuncDraws
//void D2DFunctions::DrawCircleGauge()
//{
//	//円の描画  
//	D2D1_ELLIPSE ellipse1 = D2D1::Ellipse(D2D1::Point2F(120.0F, 120.0F), 100.0F, 100.0F);
//	RenderTarget->DrawEllipse(ellipse1, GreenBrush, 10.0F);
//}
//
//void D2DFunctions::DrawRoundRectangle()
//{
//	//四角の描画  
//	D2D1_RECT_F rect1 = D2D1::RectF(100.0F, 50.0F, 300.0F, 100.F);
//	RenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(rect1, 10.0f, 10.0f), BlueBrush);
//}
//
//
//HRESULT D2DFunctions::DrawArc(ID2D1PathGeometry *pGeometry, D2D_POINT_2F ptCenterF,
//	FLOAT fRotationAngle, FLOAT fSweepAngle,
//	FLOAT fRadius,
//	D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd)
//{
//	ID2D1GeometrySink *pSink = NULL;
//
//	HRESULT hr = S_FALSE;
//
//	D2D_POINT_2F ptStartF = { 0.0f, 0.0f };
//	D2D_POINT_2F ptEndF = { 0.0f, 0.0f };
//
//	ptStartF = CalcCartesianCoordinate(fRotationAngle, fRadius);
//	ptStartF.x += ptCenterF.x;
//	ptStartF.y += ptCenterF.y;
//
//	ptEndF = CalcCartesianCoordinate(fRotationAngle + fSweepAngle, fRadius);
//	ptEndF.x += ptCenterF.x;
//	ptEndF.y += ptCenterF.y;
//
//	hr = pGeometry->Open(&pSink);
//	if (SUCCEEDED(hr)) {
//		pSink->SetFillMode(fillMode);
//
//		pSink->BeginFigure(ptCenterF, figureBegin);
//		pSink->AddLine(ptStartF);
//		pSink->AddArc(
//			D2D1::ArcSegment(
//				ptEndF,
//				D2D1::SizeF(fRadius, fRadius),
//				0.0f, // rotation angle
//				D2D1_SWEEP_DIRECTION_CLOCKWISE,
//				(fSweepAngle > 180.0f) ? D2D1_ARC_SIZE_LARGE : D2D1_ARC_SIZE_SMALL
//			));
//		pSink->EndFigure(figureEnd);
//
//		hr = pSink->Close();
//		if (SUCCEEDED(hr))
//			SAFE_RELEASE(pSink);
//	}
//	return hr;
//}
//
//HRESULT D2DFunctions::DrawPie(ID2D1PathGeometry *pGeometry, D2D_POINT_2F ptCenterF,
//	FLOAT fRotationAngle, FLOAT fSweepAngle,
//	FLOAT fOuterRadius, FLOAT fInnerRadius,
//	D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd)
//{
//	ID2D1GeometrySink *pSink = NULL;
//
//	HRESULT hr = S_FALSE;
//
//	D2D_POINT_2F ptInStartF = { 0.0f, 0.0f };
//	D2D_POINT_2F ptInEndF = { 0.0f, 0.0f };
//
//	D2D_POINT_2F ptOutStartF = { 0.0f, 0.0f };
//	D2D_POINT_2F ptOutEndF = { 0.0f, 0.0f };
//
//	ptInStartF = CalcCartesianCoordinate(fRotationAngle, fInnerRadius);
//	ptInStartF.x += ptCenterF.x;
//	ptInStartF.y += ptCenterF.y;
//
//	ptInEndF = CalcCartesianCoordinate(fRotationAngle + fSweepAngle, fInnerRadius);
//	ptInEndF.x += ptCenterF.x;
//	ptInEndF.y += ptCenterF.y;
//
//	ptOutStartF = CalcCartesianCoordinate(fRotationAngle, fOuterRadius);
//	ptOutStartF.x += ptCenterF.x;
//	ptOutStartF.y += ptCenterF.y;
//
//	ptOutEndF = CalcCartesianCoordinate(fRotationAngle + fSweepAngle, fOuterRadius);
//	ptOutEndF.x += ptCenterF.x;
//	ptOutEndF.y += ptCenterF.y;
//
//
//	hr = pGeometry->Open(&pSink);
//
//	if (SUCCEEDED(hr)) {
//		pSink->SetFillMode(fillMode);
//		pSink->BeginFigure(ptInStartF, figureBegin);
//		pSink->AddLine(ptOutStartF);
//		pSink->AddArc(
//			D2D1::ArcSegment(
//				ptOutEndF,
//				D2D1::SizeF(fOuterRadius, fOuterRadius),
//				0.0f, // rotation angle
//				D2D1_SWEEP_DIRECTION_CLOCKWISE,
//				(fSweepAngle > 180.0f) ? D2D1_ARC_SIZE_LARGE : D2D1_ARC_SIZE_SMALL
//			));
//		pSink->AddLine(ptInEndF);
//		pSink->AddArc(
//			D2D1::ArcSegment(
//				ptInStartF,
//				D2D1::SizeF(fInnerRadius, fInnerRadius),
//				0.0f, // rotation angle
//				D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE,
//				(fSweepAngle > 180.0f) ? D2D1_ARC_SIZE_LARGE : D2D1_ARC_SIZE_SMALL
//			));
//		pSink->EndFigure(figureEnd);
//
//		hr = pSink->Close();
//
//		if (SUCCEEDED(hr))
//			SAFE_RELEASE(pSink);
//	}
//	return hr;
//}
//#pragma endregion D2DFuncDraws
//
//
//
//D2D_POINT_2F D2DFunctions::CalcCartesianCoordinate(FLOAT fAngle, FLOAT fRadius)
//{
//	double dblAngleRad = 0.0f;
//	FLOAT x = 0.0f, y = 0.0f;
//
//	dblAngleRad = (M_PI / 180.0f) * (fAngle - 90.0f);
//
//	x = (FLOAT)(fRadius * cos(dblAngleRad));
//	y = (FLOAT)(fRadius * sin(dblAngleRad));
//	return D2D1::Point2F(x, y);
//}
//
//#pragma endregion D2DFunctions
//
//
