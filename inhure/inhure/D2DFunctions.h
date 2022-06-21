#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include <d2d1.h>

// lib指定
#pragma comment(lib,"d2d1.lib")

/*
*	DxgiRenaderTargetでしか機能しないかも。
*	利用しているRenderTargetごとの利用方法と設定を調べること
*/

namespace D2DFunctions
{
	class D2DFuncComponent
	{
	protected:
		// 利用するインターフェース
		static ID2D1Factory*			D2DFactory;
		static ID2D1RenderTarget*		RenderTarget;
		// デフォルトブラシ
		static ID2D1SolidColorBrush*	BlackBrush;
		static ID2D1SolidColorBrush*	BlueBrush;
		static ID2D1SolidColorBrush*	GreenBrush;
		static ID2D1SolidColorBrush*	RedBrush;
		// Init済みFlag
		static bool InitedFlag;		// true:済み/false:未初期化
		// デフォルト描画順
		static const int defDrawOrder;

	public:
		D2DFuncComponent();
		virtual ~D2DFuncComponent();

		// static変数を初期化(それぞれプログラム中に1回呼べば良い)
		// 初期化済の引数を取るのでコンストラクタには含めない設計にした->COMをきちんと利用すればできるかも?
		static HRESULT InitD2DFunc(ID2D1Factory* factory, ID2D1RenderTarget * target);
		static void UninitD2DFunc();

		virtual void Draw();

		//getter
		int	GetDrawOrder() const { return DrawOrder; }

	private:
		int DrawOrder;
	};

	class D2DGauge : public D2DFuncComponent
	{
	public:
		D2DGauge();
		~D2DGauge();

		void Draw() override;

		// Draw関数群
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

	private://ヘルパー
		D2D_POINT_2F CalcCartesianCoordinate(FLOAT fAngle, FLOAT fRadius);
	};


	/*
	*	Note : 下記関数群はテスト用に記述
	*	原因	 :	①Window.cpp(藤岡製not標準Windows)でのDraw内記述でSceneDrawがRenderTargetのクリア前に行われている
	*			②そもそもDrawコールの実装内容がRenderingEngine(藤岡製)の***_Listへのpush_backになっている
	*			(つまり***_List->render()以外のグローバルなDrawコールは全部無視される)
	*	結論 : RenderingEngineのDrawコールは実質push_back命令の実装になっているのでそれに合わせた記述が必要
	*			また、機能追加する際はRenderingEngine側に専用の***_Listを作成しなければならない
	*			(グローバル関数として好きなタイミングで呼べないので、静的なlibに手を加えなければいけない)
	*/

	//// この関数群を使う際はInit()､Uninit()を呼ぶこと
	//void InitD2DFunctions(ID2D1Factory* factory, ID2D1RenderTarget* render_target);
	//void UninitD2DFunctions();

	//void DrawCircleGauge();	//テスト
	//void DrawRoundRectangle();//テスト

	//HRESULT DrawArc(ID2D1PathGeometry *pGeometry, D2D_POINT_2F ptCenterF,
	//	FLOAT fRotationAngle, FLOAT fSweepAngle,
	//	FLOAT fRadius,
	//	D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd);

	//HRESULT DrawPie(ID2D1PathGeometry *pGeometry, D2D_POINT_2F ptCenterF,
	//	FLOAT fRotationAngle, FLOAT fSweepAngle,
	//	FLOAT fOuterRadius, FLOAT fInnerRadius,
	//	D2D1_FILL_MODE fillMode, D2D1_FIGURE_BEGIN figureBegin, D2D1_FIGURE_END figureEnd);

	//D2D_POINT_2F CalcCartesianCoordinate(FLOAT fAngle, FLOAT fRadius);


}

