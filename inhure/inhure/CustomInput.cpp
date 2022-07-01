#include "CustomInput.h"

#include "input.h"

using GI = GameInput;
#define SC_I(param) static_cast<int>(param)

CustomInput::CustomInput()
{
	// メンバ変数初期化
	for (auto&& gs : gameInputState) {
		gs = false;
	}
	for (auto&& gs : gameInputStateOld) {
		gs = false;
	}
	// input.hの初期化
	InitInput();
}

CustomInput::~CustomInput()
{
	// input.hの後処理
	UninitInput();
}

void CustomInput::Update()
{
	// 各デバイスをupdate
	UpdateInput();

	// ボタンの状態を更新する前に、以前の状態を記録しておく
	for (int i = 0; i < SC_I(GI::GAME_INPUT_NUM); i++) {
		gameInputStateOld[i] = gameInputState[i];
	}

	/*	１つ１つのゲーム用入力に対して、
	*	どのボタン、キーが押されていれば入力された扱いにするかをここで決めています。
	*/

	//スペースキーか、JOYBUTTON1(何ボタンかｼﾗﾅｲ)が
	//押されていたらジャンプボタンが押されている判定になる
	gameInputState[SC_I(GI::JUMP)] = 
		GetKeyPress(VK_SPACE) || 
		GetJoyButton(0, JOYBUTTON1);
	
	gameInputState[SC_I(GI::ATTACK)] = 
		GetKeyPress(VK_F) || 
		GetJoyButton(0, JOYBUTTON2);

	//例えば攻撃ボタンでも、ジャンプボタンでも、エンターキーでも
	//OKボタン入力の扱いにしたいときなどでも自由に設定できます。
	//こんな感じで以下省略･･･
	gameInputState[SC_I(GI::OK)] =
		gameInputState[SC_I(GI::JUMP)] ||
		gameInputState[SC_I(GI::ATTACK)] ||
		GetKeyPress(VK_RETURN);
}

bool CustomInput::getPress(GameInput input)
{
	//ボタンが押しっぱなし = 現在のフレームで押されている
	return gameInputState[SC_I(input)] == true;
}

bool CustomInput::getTrigger(GameInput input)
{
	//ボタンが押された瞬間 = 現在のフレームで押されている＋１フレーム前には押されていない
	return gameInputState[SC_I(input)] == true && gameInputStateOld[SC_I(input)] == false;
}

bool CustomInput::getRelease(GameInput input)
{
	//ボタンが離された瞬間 = 現在のフレームでは離されている＋１フレーム前には押されていた
	return gameInputState[SC_I(input)] == false && gameInputStateOld[SC_I(input)] == true;
}

#undef SC_I