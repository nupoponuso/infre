//-------------------------------------------
//
//			main�֐�
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//�C���N���[�h
#include <Windows.h>
#include <tchar.h>
#include "MainWindow.h"

#define Name _T("����")

//�O���[�o���ϐ�
//GamwWindow�N���X�̃|�C���^
F_lib_Fremworker::GameWindow * GWin = nullptr;



//���C���֐�
//�S�Ă̏���
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
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
