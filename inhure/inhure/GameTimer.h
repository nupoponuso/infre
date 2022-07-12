#pragma once

#include <Windows.h>

namespace F_lib_Render
{
	class D2DTextParams;
}

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
	bool Pause;			// 一時停止 true:している/false:していない
	DWORD CurrentTime;	// 計算用現在時間
	double TimerCount;	// 出力用経過時間
#ifdef _DEBUG
	F_lib_Render::D2DTextParams* CountText;	// デバッグ用カウント表示
#endif // _DEBUG
};

