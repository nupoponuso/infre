#pragma once

#include "comon.h"
#include "D2DText.h"

class GameTimer
{
public:
	GameTimer();
	~GameTimer();

	void restart();		// 計測開始秒を保存
	double elapsed();	// リスタートからの秒数を返す

	void Update();
	void Draw();	// 実装内容はテスト段階

	bool IsPause();

private:
	bool Pause;		// 一時停止 true:している/false:していない
	DWORD CurrentTime;
	double TimerCount;
	F_lib_Render::D2DText* CountText;
};

