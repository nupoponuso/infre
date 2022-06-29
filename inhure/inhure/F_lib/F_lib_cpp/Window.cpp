//-------------------------------------------
//
//　	comon.hの関数とGameWindowクラス
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//インクルード
#include "Window.h"
#include "comon.h"
#include "RenderingEngine.h"

//#include "input.h"
#include "sound.h"


//定数宣言
#define SHADOW_NUM (2)

//グローバル変数
F_lib_Fremworker::GameWindow* Pwindow = nullptr;
POINT ClientMousePos = { -1,-1 };


//-------------------------------------------------------
//
//   comon.hのC関数
//
//-------------------------------------------------------

//メッセージプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//メッセージプロシージャ
LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return Pwindow->MsgProc(hWnd, uMsg, wParam, lParam);
}


//--------------------------------------------------------
//
//GameWindowクラス
//
//--------------------------------------------------------


namespace F_lib_Fremworker
{
	using namespace F_lib_Render;


	//InitWindow関数
	//ウィンドウの生成
	HRESULT GameWindow::InitWindow(InitdataGameWindow _dat)
	{
		Pwindow = this;

		WNDCLASSEX wcex =
		{
			sizeof(WNDCLASSEX),
			CS_CLASSDC,
			WndProc,
			0,
			0,
			_dat.hins,
			LoadIcon(_dat.hins,IDC_ICON),
			LoadCursor(nullptr,IDC_ARROW),
			(HBRUSH)(COLOR_WINDOW + 1),
			nullptr,
			_dat.windowName,
			nullptr,

		};

		RegisterClassEx(&wcex);

		DWORD dwstyle = WS_OVERLAPPED | WS_CAPTION
			| WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;

		hWnd = CreateWindow(_dat.windowName, _dat.windowName, dwstyle, _dat.WindowPos.x, _dat.WindowPos.y, _dat.WindowSize.x, _dat.WindowSize.y, 0, 0, _dat.hins, 0);

		RECT window_rect, client_rect;
		XMFLOAT2 frame_size;

		GetWindowRect(hWnd, &window_rect);
		GetClientRect(hWnd, &client_rect);

		frame_size.x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
		frame_size.y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);

		SetWindowPos(hWnd, NULL, CW_USEDEFAULT, 0, frame_size.x + _dat.WindowSize.x, frame_size.y + _dat.WindowSize.y, SWP_NOMOVE);

		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);

		return E_NOTIMPL;
	}


	//InitD3D関数
	//DirectX11の初期化
	HRESULT GameWindow::InitD3D(INT width, INT  height)
	{

		Engine = new RenderingEngine();
		Engine->Iint(hWnd, width, height);

		init();

		return S_OK;

	}


	//MsgProc関数
	//GameWindowクラスのメッセージプロシージャ
	LRESULT GameWindow::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (iMsg)
		{
		case WM_KEYDOWN:
			switch ((char)wParam) {
			case VK_ESCAPE:
				int ret = MessageBox(hWnd, TEXT("終了しますか?"), TEXT("終了確認"), MB_OKCANCEL);
				if (ret == IDOK) {
					//PostQuitMessage(0);
					DestroyWindow(hWnd);
				}
				break;
			}
			break;
		case WM_MOUSEMOVE:
			ClientMousePos.x = LOWORD(lParam);
			ClientMousePos.y = HIWORD(lParam);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}

		return DefWindowProc(hWnd, iMsg, wParam, lParam);

	}


	//Loop関数
	//メインループ
	void GameWindow::Loop()
	{
		MSG msg = { 0 };
		ZeroMemory(&msg, sizeof(msg));

		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

			}
			else process();

		}

		DestroyD3D();

	}


	//DestroyD3D関数
	//D3Dの開放
	void GameWindow::DestroyD3D()
	{
		

	}


	//process関数
	//更新と描画のまとめ
	void GameWindow::process()
	{
		if (FpsManager->update())
		{
			Update();
			Draw();

		}

		FpsManager->Freamecount();
	}


	//init関数
	//初期化
	void GameWindow::init()
	{
		srand((unsigned int)time(NULL));
		FpsManager = Fpsmaneger::getins();
	

	}


	//Update関数
	//更新
	void GameWindow::Update()
	{
		Scene->updateScene();

	}


	//Draw関数
	//描画
	void GameWindow::Draw()
	{
		Scene->DrawScene();
		Engine->Renderring();

	}

}


POINT GetClientMousePos()
{
	return ClientMousePos;
}