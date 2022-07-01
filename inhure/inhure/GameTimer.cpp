#include "GameTimer.h"

#include "RenderingEngine.h"
#include "D2DDrawMng.h"
#include "D2DText.h"
#include "input.h"

// ŒOóÔÌéŸ
using namespace F_lib_Render;

GameTimer::GameTimer()
	: Pause(false)
	, TimerCount(0.0f)
{
	restart();
<<<<<<< HEAD
	//CountText = new D2DText();
=======
	CountText = new D2DTextParams();
>>>>>>> D2Dæ©èœå°å¥ãåã³ã«ã¹ã¿ã ã€ã³ãããéçºéå§
}

GameTimer::~GameTimer()
{
	delete CountText;
}

void GameTimer::restart()
{
	CurrentTime = timeGetTime();
}

double GameTimer::elapsed()
{
	DWORD end = timeGetTime();
	return static_cast<double>(end - CurrentTime) / 1000;
}

void GameTimer::Update()
{
	if (GetKeyTrigger(VK_K)) {
		Pause = true;
	} else if(GetKeyTrigger(VK_I)) {
		Pause = false;
	}

	if (!Pause) {
		TimerCount += elapsed();
		restart();
	} else {
		restart();
		TimerCount += elapsed();
		restart();
	}
#ifdef _DEBUG
<<<<<<< HEAD
	//TCHAR str[256];
	//_stprintf_s(str, 256, TEXT("Pause : %d / TimerCount : %10.2f"), Pause, TimerCount);
	//
=======
	TCHAR str[MAXCHAR];
	_stprintf_s(str, MAXCHAR, TEXT("Pause : %d / TimerCount : %10.2f"), Pause, TimerCount);
	
>>>>>>> D2Dæ©èœå°å¥ãåã³ã«ã¹ã¿ã ã€ã³ãããéçºéå§
	//int nLen = ::MultiByteToWideChar(CP_THREAD_ACP, 0, str, -1, NULL, 0);
	//WCHAR* wstr = new WCHAR[nLen];
	//if (wstr) {
	//	//Ï·
	//	nLen = ::MultiByteToWideChar(CP_THREAD_ACP, 0, str, (int)::strlen(str) + 1, wstr, nLen);
	//	if (nLen == 0) {
	//		delete	wstr;
	//		wstr = NULL;
	//	}
	//}
<<<<<<< HEAD
	//CountText->SetText(wstr);
	//CountText->SetRect(D2D_RECT_F{ 400,0,600,200 });
	//
=======

	TextData td;
	td.Str = str;
	td.Rect = { 400, 0, 600, 200 };
	td.Data->font = Font::Arial;
	td.Data->fontSize = 30;
	td.Data->Opacity = 0.6f;
	if (GetKeyPress(VK_SPACE)) {
		CountText->SetDrawFlag(false);
		//td.DrawFlag = !td.DrawFlag;
	} else {
		CountText->SetDrawFlag(true);
	}
	//FontData fd;
	//fd.font = Font::MeiryoUI;
	//fd.fontSize = 10;
	//fd.Opacity = 0.5f;
	//getEngine()->getD2DText()->SetFont(&fd);
	CountText->SetData(&td);
	//delete fd;
	//getEngine()->getD2DText()->SetFont(&fd);
	//CountText->SetText(wstr, nLen);
	//CountText->SetRect(D2D_RECT_F{ 400,0,600,200 });

>>>>>>> D2Dæ©èœå°å¥ãåã³ã«ã¹ã¿ã ã€ã³ãããéçºéå§
	//delete wstr;
	//wstr = nullptr;
#endif // _DEBUG

}

void GameTimer::Draw()
{
	//TCHAR str[256];
	//_stprintf_s(str, 256, TEXT("Pause : %d / TimerCount : %10.2f"), Pause, TimerCount);

	//int nLen = ::MultiByteToWideChar(CP_THREAD_ACP, 0, str, -1, NULL, 0);
	//WCHAR* wstr = new WCHAR[nLen];
	//if (wstr) {
	//	//Ï·
	//	nLen = ::MultiByteToWideChar(CP_THREAD_ACP, 0, str, (int)::strlen(str) + 1, wstr, nLen);
	//	if (nLen == 0) {
	//		delete	wstr;
	//		wstr = NULL;
	//	}
	//}
	//CountText->setPosition(XMFLOAT2(100.0f, 10.0f));
	//CountText->draw(wstr);

	//delete wstr;
	//wstr = nullptr;
}

bool GameTimer::IsPause()
{
	if (Pause) {
		return true;
	} else {
		return false;
	}
}
