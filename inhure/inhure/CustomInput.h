#pragma once

//ゲームに必要な入力の種類
enum class GameInput
{
	OK = 0,				//OKボタン
	CANCEL,				//キャンセルボタン
	PAUSE,				//ポーズボタン
	JUMP,				//ジャンプボタン
	ATTACK,				//攻撃ボタン

	GAME_INPUT_NUM		//ボタンの種類の数
};

/* @brief : Wrapper of input.h.Bind "Action Button" to device input.
*/
class CustomInput
{
public:
	CustomInput();
	~CustomInput();

	void Update();		// ボタンが押されているかどうかを更新する

	/* @brief
	*  @[in] input : enum class GameInput
	*  -Recommendation. Use following sentence
	*  using GI = GameInput;
	*  #define SC_I(param) static_cast<int>(param)
	*  #undef SC_I
	*/
	bool GetCustomInputPress(GameInput input);		//ボタンが押されている間はtrueを返す
	bool GetCustomInputTrigger(GameInput input);	//ボタンが押された瞬間だけtrueを返す
	bool GetCustomInputRelease(GameInput input);	//ボタンが離された瞬間だけtrueを返す

private:
	bool gameInputState[static_cast<int>(GameInput::GAME_INPUT_NUM)];		//全てのボタンごとに、押されているかどうかを記録する変数
	bool gameInputStateOld[static_cast<int>(GameInput::GAME_INPUT_NUM)];	//前フレームでの入力状態を記録するための変数

};

