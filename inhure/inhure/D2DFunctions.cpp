#include "D2DFunctions.h"

#include "D2DDrawMng.h"
#include "RenderingEngine.h"	//インスタンスの取得(D2DRenderTargetsAndDWrite, D2DDrawMng)
#include "D2DRenderTargetsAndDWrite.h"
#include "D2DDrawMng.h"

using namespace F_lib_Render;

namespace D2DFunctions
{
	// staticメンバーの初期化
	// デフォルト描画順
	const int D2DFuncComponent::defDrawOrder = 100;


#pragma region D2DFuncInitialize
	HRESULT D2DFuncComponent::Init(ID2D1Factory * factory, F_lib_Render::D2DFuncMng* drawer)
	{
		HRESULT hr = S_OK;

		// 必須インターフェースのポインタを取得
		if (D2DFactory == nullptr) {
			D2DFactory = factory;
			D2DFactory->AddRef();
		}

		if (Manager = nullptr) {
			Manager = drawer;
		}
		return hr;
	}
#pragma endregion D2DFuncInitialize



#pragma region D2DFuncBase
	D2DFuncComponent::D2DFuncComponent()
		: RenderTargetResources(getEngine()->getD2DTargets()->GetDxgiRenderTarget())
		, DrawOrder(defDrawOrder)
		, DrawFlag(true)
		, Manager(nullptr)
		, D2DFactory(nullptr)
	{
		Init(getEngine()->getD2DTargets()->GetD2DFactory(), getEngine()->getD2DFuncMng());
		// 生成したら即登録
		Manager->Add(this);
	}

	D2DFuncComponent::~D2DFuncComponent()
	{
		Manager->Remove(this);
		Manager = nullptr;
		SAFE_RELEASE(D2DFactory);
	}
	
	void D2DFuncComponent::Draw()
	{
		// 仮想関数
	}

#pragma region D2DDrawFunctions
	//円の描画
	void D2DFuncComponent::DrawCircleGauge()
	{
		D2D1_ELLIPSE ellipse1 = D2D1::Ellipse(D2D1::Point2F(120.0F, 120.0F), 100.0F, 100.0F);
		RenderTarget->DrawEllipse(ellipse1, GreenBrush, 10.0F);
	}
	//四角の描画
	void D2DFuncComponent::DrawRoundRectangle()
	{
		D2D1_RECT_F rect1 = D2D1::RectF(100.0F, 50.0F, 300.0F, 100.F);
		RenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(rect1, 10.0f, 10.0f), BlueBrush);
	}
	HRESULT D2DFuncComponent::DrawArc(ID2D1PathGeometry * pGeometry, D2D_POINT_2F ptCenterF, FLOAT fRotationAngle, FLOAT fSweepAngle, FLOAT fRadius, D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd)
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
	HRESULT D2DFuncComponent::DrawPie(ID2D1PathGeometry * pGeometry, D2D_POINT_2F ptCenterF, FLOAT fRotationAngle, FLOAT fSweepAngle, FLOAT fOuterRadius, FLOAT fInnerRadius, D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd)
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
	void D2DFuncComponent::SetDrawOrder(int drawOrder)
	{
		Manager->ChangeDrawOrder(this, drawOrder);
		DrawOrder = drawOrder;
	}
#pragma endregion D2DDrawFunctions


#pragma region D2DFuncHelper
	D2D_POINT_2F D2DFuncComponent::CalcCartesianCoordinate(FLOAT fAngle, FLOAT fRadius)
	{
		double dblAngleRad = 0.0f;
		FLOAT x = 0.0f, y = 0.0f;

		dblAngleRad = (M_PI / 180.0f) * (fAngle - 90.0f);

		x = (FLOAT)(fRadius * cos(dblAngleRad));
		y = (FLOAT)(fRadius * sin(dblAngleRad));
		return D2D1::Point2F(x, y);
	}
#pragma endregion D2DFuncHelper
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
#pragma endregion D2DInheritance
}

