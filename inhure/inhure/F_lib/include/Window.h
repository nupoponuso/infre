
//-------------------------------------------
//
//�@	GameWindow�N���X�@| GameWindow.cpp |
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once


//�C���N���[�h
#include "comon.h"
#include "SceneManeger.h"
#include "RenderingEngine.h"
#include "Fpsmaneger.h"
//#include "inputManeger.h"


namespace F_lib_Fremworker
{

	struct InitdataGameWindow
	{
		HINSTANCE hins;
		XMFLOAT2 WindowPos, WindowSize;

#ifdef _DEBUG
		LPCSTR windowName;
#else
		LPCWSTR windowName;
#endif

		InitdataGameWindow()
		{
#ifdef _DEBUG
			windowName = "���̃E�B���h�E�ɖ��O���Ȃ�";
#else
			windowName = L"���̃E�B���h�E�ɖ��O���Ȃ�";
#endif
			WindowPos.x = WindowPos.y = 0;

		}

	};


	//�@GameWindow�N���X
	//�@�N���X�����o
	class GameWindow
	{
	public:
		HRESULT InitWindow(InitdataGameWindow);

		HRESULT InitD3D(INT, INT);
		LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

		void Loop();
		void DestroyD3D();

		HWND GetWind() { return hWnd; }

	protected:
		void process();
		virtual void init();
		void Update();
		void Draw();

		HWND hWnd;

		SceneManeger* Scene;
		Fpsmaneger*   FpsManager;
		F_lib_Render::RenderingEngine* Engine;
		//inputManeger* inputm;

	};

}