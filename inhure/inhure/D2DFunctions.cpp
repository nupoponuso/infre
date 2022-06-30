#include "D2DFunctions.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "D2DDrawMng.h"
#include "RenderingEngine.h"	//インスタンスの取得(D2DRenderTargetsAndDWrite, D2DDrawMng)
#include "D2DRenderTargetsAndDWrite.h"


namespace D2DFunctions
{
#pragma region D2DFuncHelper
	D2D_POINT_2F CalcCartesianCoordinate(FLOAT fAngle, FLOAT fRadius)
	{
		double dblAngleRad = 0.0f;
		FLOAT x = 0.0f, y = 0.0f;

		dblAngleRad = (M_PI / 180.0f) * (fAngle - 90.0f);

		x = (FLOAT)(fRadius * cos(dblAngleRad));
		y = (FLOAT)(fRadius * sin(dblAngleRad));
		return D2D1::Point2F(x, y);
	}
#pragma endregion D2DFuncHelper

#pragma region D2DFunctions
	HRESULT DrawArc(ID2D1PathGeometry * pGeometry, D2D_POINT_2F ptCenterF,
		FLOAT fRotationAngle, FLOAT fSweepAngle,
		FLOAT fRadius,
		D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd)
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
	HRESULT DrawPie(ID2D1PathGeometry * pGeometry, D2D_POINT_2F ptCenterF,
		FLOAT fRotationAngle, FLOAT fSweepAngle,
		FLOAT fOuterRadius, FLOAT fInnerRadius,
		D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd)
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

	////円の描画
	//void D2DFuncComponent::DrawCircleGauge()
	//{
	//	D2D1_ELLIPSE ellipse1 = D2D1::Ellipse(D2D1::Point2F(120.0F, 120.0F), 100.0F, 100.0F);
	//	RenderTarget->DrawEllipse(ellipse1, GreenBrush, 10.0F);
	//}
	////四角の描画
	//void D2DFuncComponent::DrawRoundRectangle()
	//{
	//	D2D1_RECT_F rect1 = D2D1::RectF(100.0F, 50.0F, 300.0F, 100.F);
	//	RenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(rect1, 10.0f, 10.0f), BlueBrush);
	//}

#pragma endregion D2DFunctions
}



namespace F_lib_Render
{
#pragma region D2DFuncBase
	// staticメンバーの初期化
	// デフォルト描画順
	const int D2DFuncComponent::defDrawOrder = 100;

	D2DFuncComponent::D2DFuncComponent()
		: DrawOrder(defDrawOrder)
		, DrawFlag(true)
	{
		//外部インスタンスの場所が判明しているので、今回は直接取得している
		RenderTarget = getEngine()->getD2DTargets()->GetDxgiRenderTarget();
		RenderTarget->AddRef();
		D2DFactory = getEngine()->getD2DTargets()->GetD2DFactory();
		D2DFactory->AddRef();
		Manager = getEngine()->getD2DFuncMng();

		// 生成したら即登録
		Manager->Add(this);
	}

	D2DFuncComponent::~D2DFuncComponent()
	{
		Manager->Remove(this);
		Manager = nullptr;
		SAFE_RELEASE(RenderTarget);
		SAFE_RELEASE(D2DFactory);
	}

	void D2DFuncComponent::Render()
	{
		RenderTarget->BeginDraw();
		RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		//RenderTarget->Clear()はRenderingEngine側で行っているので、ここでやってはダメ

		Draw();	// オーバーライドされた処理が入る

		RenderTarget->EndDraw();
	}
	
	void D2DFuncComponent::Draw()
	{
		// 仮想関数
	}

	void D2DFuncComponent::SetDrawOrder(int drawOrder)
	{
		Manager->ChangeDrawOrder(this, drawOrder);
		DrawOrder = drawOrder;
	}
#pragma endregion D2DFuncBase



#pragma region D2DInheritance
	D2DCircleGauge::D2DCircleGauge()
		: GaugeGeometry(nullptr)
		, FillBrush(nullptr)
		, Center({0,0})
		, InnerRadius(0)
		, OuterRaidus(0)
	{
		// 何もしない
	}

	D2DCircleGauge::~D2DCircleGauge()
	{
		SAFE_RELEASE(GaugeGeometry);
		SAFE_RELEASE(FillBrush);
	}
	
	void D2DCircleGauge::Draw()
	{
		if (DrawFlag == true) {
			FillBrush->SetColor(D2D1::ColorF(D2D1::ColorF::LightCoral));
			RenderTarget->FillGeometry(GaugeGeometry, FillBrush);	//塗りつぶし
			FillBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Crimson));
			RenderTarget->DrawGeometry(GaugeGeometry, FillBrush);	//外枠
		}
	}
	
	HRESULT D2DCircleGauge::Create(D2D_POINT_2F center, FLOAT outerRadius, FLOAT innerRadius)
	{
		HRESULT hr = S_OK;

		// リソース生成
		hr = D2DFactory->CreatePathGeometry(&GaugeGeometry);
		if (FAILED(hr)) return hr;
		hr = RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightCoral), &FillBrush);
		if (FAILED(hr)) return hr;

		// パラメータ初期化
		FillBrush->SetOpacity(0.75f);
		Center = center;
		OuterRaidus = outerRadius;
		InnerRadius = innerRadius;

		// ジオメトリの作成
		hr = DrawPie(GaugeGeometry, center,
			0.0f, 359.0f,
			outerRadius, innerRadius,
			D2D1_FILL_MODE_WINDING, D2D1_FIGURE_BEGIN_HOLLOW, D2D1_FIGURE_END_CLOSED);
		if (FAILED(hr)) return hr;

		return hr;
	}
	
	void D2DCircleGauge::Update()
	{
		DrawPie(GaugeGeometry, Center,
			90.0f, 360.0f,
			OuterRaidus, InnerRadius,
			D2D1_FILL_MODE_WINDING, D2D1_FIGURE_BEGIN_FILLED, D2D1_FIGURE_END_CLOSED);
		
	}
#pragma endregion D2DInheritance
}

