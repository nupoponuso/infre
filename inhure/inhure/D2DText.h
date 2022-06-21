#pragma once

#include <vector>
#include <DirectXColors.h>
#include <d2d1.h>
#include <dwrite.h>

#include "RenderTargetResources.h"	// レンダーターゲットリソースをまとめてあるクラス

// lib指定
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

//前方宣言
namespace F_lib_Render
{
class D2DTextMng;
}

namespace F_lib_Render
{
	class D2DText : public RenderTargetResources
	{
	protected:
		// 利用するインターフェース
		static IDWriteFactory*		DWriteFactory;
		// デフォルトフォントパラメータ
		static const WCHAR*			defFontFamiry;
		static const float			defFontSize;
		static D2D1_COLOR_F			defFontColor;
		static IDWriteTextFormat*	defTextFormat;
		// デフォルト描画順
		static const int defDrawOrder;
		//// 描画管理クラス
		//static D2DTextMng* Manager;
		// staticで持ちたいが上手くいかないので一旦別の方法で実装する

	public:
		D2DText();
		D2DText(const std::wstring str, D2D1_RECT_F rect, int drawOrder = defDrawOrder);
		D2DText(const WCHAR* str, int length, D2D1_RECT_F rect, int drawOrder = defDrawOrder);
		~D2DText();
		
		// static変数を初期化(それぞれプログラム中に1回呼べば良い)
		// factoryのポインタを取得(必須)
		static HRESULT Init(IDWriteFactory* factory, D2DTextMng* drawer);
		static void Uninit();

		// 生成用関数(DWriteFactoryメソッドのラッパー)
		HRESULT CreateTextFormat(const WCHAR* fontFamiyName, float fontSize);
		HRESULT CreateSolidBrush(D2D1_COLOR_F& c);
		

		//setter
		void SetText(std::wstring str);
		void SetText(WCHAR* str, int length);
		void SetRect(D2D1_RECT_F rect);
		void SetDrawFlag(bool enable);
		void SetFontSize(float size);
		void SetColor(D2D1_COLOR_F color);
		void SetOpacity(float alpha);

		// getter
		IDWriteFactory*			GetDWriteFactory() const { return DWriteFactory; }
		IDWriteTextFormat*		GetTextFormat() const { return TextFormat; }
		ID2D1SolidColorBrush*	GetSolidBrush() const { return SolidBrush; }
		const WCHAR*	GetText()		const { return Text; }
		int				GetTextLength()	const { return TextLength; }
		D2D1_RECT_F		GetDrawRect()	const { return DrawRect; }
		int				GetDrawOrder()	const { return DrawOrder; }
		bool			GetDrawFlag()	const { return DrawFlag; }
	private:
		// 生成メンバ
		IDWriteTextFormat*		TextFormat;		// 各文字列は固有値を保持するものとする
		ID2D1SolidColorBrush*	SolidBrush;		// 各文字列は固有値を保持するものとする
		const WCHAR*	Text;		// 表示文字列
		int				TextLength;	// 文字数
		D2D1_RECT_F		DrawRect;	// 文字列を描画する長方形
		int				DrawOrder;	// 文字列の描画順を指定する(大きいほど手前表示)
		bool			DrawFlag;	// Drawerに描画させるかを指示(true:描画する/false:しない)
		D2DTextMng*		Manager;
	};
}
