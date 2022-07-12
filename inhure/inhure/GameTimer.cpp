#include "GameTimer.h"

#include "RenderingEngine.h"
#include "D2DDrawMng.h"
#include "D2DText.h"
#include "input.h"

// 名前空間の宣言
using namespace F_lib_Render;

GameTimer::GameTimer()
	: Pause(false)
	, TimerCount(0.0f)
{
	restart();
#ifdef _DEBUG
	CountText = new D2DTextParams();
#endif // _DEBUG
}

GameTimer::~GameTimer()
{
#ifdef _DEBUG
	delete CountText;
#endif // _DEBUG
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
#ifdef _DEBUG
	// ポーズ機能テスト用
	if (GetKeyTrigger(VK_K)) {
		Pause = true;
	} else if(GetKeyTrigger(VK_I)) {
		Pause = false;
	}
#endif // _DEBUG

	if (!Pause) {
		TimerCount += elapsed();
		restart();
	} else {
		restart();
		TimerCount += elapsed();
		restart();
	}

#ifdef _DEBUG
	// 経過時間のチェック用
	TCHAR str[MAXCHAR];
	_stprintf_s(str, MAXCHAR, TEXT("Pause : %d / TimerCount : %10.2f"), Pause, TimerCount);
	
	TextData td;
	td.Str = str;
	td.Pos = { 0,800 / 2 };
	td.Rect = { 0, 800/2, 600, 200 };
	td.Data->font = Font::Arial;
	td.Data->fontSize = 30;
	td.Data->Opacity = 0.6f;
	if (GetKeyPress(VK_P)) {
		CountText->SetDrawFlag(false);
	} else {
		CountText->SetDrawFlag(true);
	}
	CountText->SetData(&td);

#endif // _DEBUG

}

void GameTimer::Draw()
{
}

bool GameTimer::IsPause()
{
	if (Pause) {
		return true;
	} else {
		return false;
	}
}
