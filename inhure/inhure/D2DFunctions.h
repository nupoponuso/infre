#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include <d2d1.h>

#include "RenderTargetResources.h"	// レンダーターゲットリソースをまとめてあるクラス

// lib指定
#pragma comment(lib,"d2d1.lib")

/*
*	DxgiRenaderTargetでしか機能しないかも。
*	利用しているRenderTargetごとの利用方法と設定を調べること
*/

// 前方宣言
namespace F_lib_Render
{
	class D2DFuncMng;
}
//ここまで

namespace D2DFunctions
{
	class D2DFuncComponent : public F_lib_Render::RenderTargetResources
	{
	protected:
		// デフォルト描画順
		static const int defDrawOrder;

	public:
		D2DFuncComponent();
		virtual ~D2DFuncComponent();
	private:
		//Init用ヘルパー
		HRESULT Init(ID2D1Factory* factory, F_lib_Render::D2DFuncMng* drawer);
		//計算用ヘルパー
		D2D_POINT_2F CalcCartesianCoordinate(FLOAT fAngle, FLOAT fRadius);

	public:
		virtual void Draw() = 0;
		/*	@brief : Draw Functions
		*	Inherited classes should implement the desired behavior using the following set of functions.
		*	Describe in "Draw()"
		*	Mostly wrapper functions, and using the D2D1:: implementation.
		*/
		void DrawCircleGauge();
		void DrawRoundRectangle();
		HRESULT DrawArc(ID2D1PathGeometry *pGeometry, D2D_POINT_2F ptCenterF,
			FLOAT fRotationAngle, FLOAT fSweepAngle,
			FLOAT fRadius,
			D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd);
		HRESULT DrawPie(ID2D1PathGeometry *pGeometry, D2D_POINT_2F ptCenterF,
			FLOAT fRotationAngle, FLOAT fSweepAngle,
			FLOAT fOuterRadius, FLOAT fInnerRadius,
			D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd);

		//setter
		void SetDrawOrder(int drawOrder);
		void SetDrawFlag(bool enable) { DrawFlag = enable; }
		//getter
		int		GetDrawOrder()	const { return DrawOrder; }
		bool	GetDrawFlag()	const { return DrawFlag; }

	private:
		int		DrawOrder;
		bool	DrawFlag;	// Drawerに描画させるかを指示(true:描画する/false:しない)
		F_lib_Render::D2DFuncMng* Manager;	// 描画管理クラス
		ID2D1Factory* D2DFactory;			// 利用するインターフェース
	};

	class D2DGauge : public D2DFuncComponent
	{
	public:
		D2DGauge();
		~D2DGauge();

		void Draw() override;

	};
}