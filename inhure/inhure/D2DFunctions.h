#pragma once

// 参考サイト
// https://stpetrus27.wordpress.com/2010/05/02/vc-direct2d-arc-pie/
// https://docs.microsoft.com/ja-jp/windows/win32/direct2d/path-geometries-overview

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
	//計算用ヘルパー
	D2D_POINT_2F CalcCartesianCoordinate(FLOAT fAngle, FLOAT fRadius);

	/* @brief : 扇形状
	*  @param[out]	: pGeometry ジオメトリデータの保存先
	*  @param[in]	: ptCenterF 扇型の中心位置
	*  @param[in]	: fRotationAngle 開始点の画面上での絶対角度(Degree, 右回り)		*0
	*  @param[in]	: fSweepAngle 終了点の開始点からの相対角度(Degree, 右回り)	270* *90
	*  @param[in]	: fRadius 中心位置からの半径										*180		
	*  @param[in]	: fillMode 塗りつぶし方法設定
						D2D1_FILL_MODE_WINDING : 右回りなら塗りつぶし、左回りならくり抜き
						D2D1_FILL_MODE_ALTERNATE : 複数のジオメトリが重なった時に内側をくり抜く
	*  @param[in]	: figureBegin 塗りつぶすか否か設定
						D2D1_FIGURE_BEGIN_FILLED	図形を塗りつぶす
						D2D1_FIGURE_BEGIN_HOLLOW	図形を塗りつぶさない
	*  @param[in]	: figureEnd
						D2D1_FIGURE_END_OPEN	パスを閉じない
						D2D1_FIGURE_END_CLOSED	パスを閉じる
	*/ 
	HRESULT DrawArc(ID2D1PathGeometry *pGeometry, D2D_POINT_2F ptCenterF,
		FLOAT fRotationAngle, FLOAT fSweepAngle,
		FLOAT fRadius,
		D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd);
	/* @brief : 中抜き扇形状, 基本パラメータはDrawArcと同じ
	*  @param[in]	: fOuterRadius 中心位置からの外側半径
	*  @param[in]	: fInnerRadius 中心位置からの内側半径
	*/
	HRESULT DrawPie(ID2D1PathGeometry *pGeometry, D2D_POINT_2F ptCenterF,
		FLOAT fRotationAngle, FLOAT fSweepAngle,
		FLOAT fOuterRadius, FLOAT fInnerRadius,
		D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd);
	//void DrawCircleGauge();
	//void DrawRoundRectangle();
}

namespace F_lib_Render
{
	class D2DFuncComponent
	{
	protected:
		// デフォルト描画順
		static const int defDrawOrder;

	public:
		D2DFuncComponent();
		virtual ~D2DFuncComponent();

		/*	@brief : Draw Functions
		*	Inherited classes should implement the desired behavior using the following set of functions.
		*	Describe in "Draw()"
		*   RenderTarget.BeginDraw() - RenderTarget.EndDraw()
		*	Mostly wrapper functions, and using the D2D1:: implementation.
		*/
		void Render();
		virtual void Draw() = 0;

	public:
		//setter
		void SetDrawOrder(int drawOrder);
		void SetDrawFlag(bool enable) { DrawFlag = enable; }
		//getter
		int		GetDrawOrder()	const { return DrawOrder; }
		//bool	GetDrawFlag()	const { return DrawFlag; }

	protected:
		int		DrawOrder;
		bool	DrawFlag;	// Drawerに描画させるかを指示(true:描画する/false:しない)
		// 外部インスタンスのポインタ
		ID2D1RenderTarget* RenderTarget;	// 利用するレンダーターゲット
		ID2D1Factory* D2DFactory;			// 利用するインターフェース
		F_lib_Render::D2DFuncMng* Manager;	// 描画管理クラス
	};


	class D2DCircleGauge : public D2DFuncComponent
	{
	public:
		D2DCircleGauge();
		~D2DCircleGauge();

		void Draw() override;

		HRESULT Create(D2D_POINT_2F center, FLOAT outerRadius, FLOAT innerRadius);
		void Update();

	private:
		// 生成メンバ
		ID2D1PathGeometry* GaugeGeometry;
		ID2D1SolidColorBrush* FillBrush; //プログラム内で共通ブラシを作った方が良いが、管理方法を思いつかないので、取り敢えず個別に保持させる

		D2D_POINT_2F Center;
		FLOAT OuterRaidus;
		FLOAT InnerRadius;
	};
}