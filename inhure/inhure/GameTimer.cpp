#include "GameTimer.h"

#include "RenderingEngine.h"
#include "D2DDrawMng.h"
#include "D2DText.h"
#include "input.h"

// –¼‘O‹óŠÔ‚ÌéŒ¾
using namespace F_lib_Render;

GameTimer::GameTimer()
	: Pause(false)
	, TimerCount(0.0f)
{
	restart();
	CountText = new D2DText();
}

GameTimer::~GameTimer()
{
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
	TCHAR str[256];
	_stprintf_s(str, 256, TEXT("Pause : %d / TimerCount : %10.2f"), Pause, TimerCount);
	
	int nLen = ::MultiByteToWideChar(CP_THREAD_ACP, 0, str, -1, NULL, 0);
	WCHAR* wstr = new WCHAR[nLen];
	if (wstr) {
		//•ÏŠ·
		nLen = ::MultiByteToWideChar(CP_THREAD_ACP, 0, str, (int)::strlen(str) + 1, wstr, nLen);
		if (nLen == 0) {
			delete	wstr;
			wstr = NULL;
		}
	}
	CountText->SetText(wstr);
	CountText->SetRect(D2D_RECT_F{ 400,0,600,200 });

	delete wstr;
	wstr = nullptr;
#endif // _DEBUG

}

void GameTimer::Draw()
{
	//TCHAR str[256];
	//_stprintf_s(str, 256, TEXT("Pause : %d / TimerCount : %10.2f"), Pause, TimerCount);

	//int nLen = ::MultiByteToWideChar(CP_THREAD_ACP, 0, str, -1, NULL, 0);
	//WCHAR* wstr = new WCHAR[nLen];
	//if (wstr) {
	//	//•ÏŠ·
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
