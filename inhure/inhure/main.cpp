//-------------------------------------------
//
//			main関数
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//インクルード
#include <Windows.h>
#include <tchar.h>
#include "MainWindow.h"

#define Name _T("実験")

//グローバル変数
//GamwWindowクラスのポインタ
F_lib_Fremworker::GameWindow * GWin = nullptr;



//メイン関数
//全ての処理
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）
	using namespace F_lib_Fremworker;
	
	GWin = new MainWindow();
	if (GWin != nullptr)
	{
		InitdataGameWindow init;
		init.hins = hInstance;
		init.windowName = Name;
		init.WindowSize = XMFLOAT2(1280, 800);
	
		GWin->InitWindow(init);
		GWin->InitD3D((INT)init.WindowSize.x, (INT)init.WindowSize.y);
	
	}
	
	GWin->Loop();

	//delete GWin;

	return 0;
}
