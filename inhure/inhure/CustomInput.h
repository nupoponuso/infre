#pragma once

#include "singlton.h"

//�Q�[���ɕK�v�ȓ��͂̎��
enum class GameInput
{
	OK = 0,				//OK�{�^��
	CANCEL,				//�L�����Z���{�^��
	PAUSE,				//�|�[�Y�{�^��
	JUMP,				//�W�����v�{�^��
	ATTACK,				//�U���{�^��

	GAME_INPUT_NUM		//�{�^���̎�ނ̐�
};

/* @brief : Wrapper of input.h.Bind "Action Button" to device input.
*/
class CustomInput : public Singleton<CustomInput>
{
public:
	friend class Singleton <CustomInput>;

	void Update();		// �{�^����������Ă��邩�ǂ������X�V����

	/* @brief
	*  @[in] input : enum class GameInput
	*  -Recommendation. Use following sentence
	*  using GI = GameInput;
	*  #define SC_I(param) static_cast<int>(param)
	*  #undef SC_I
	*/
	bool getPress(GameInput input);		//�{�^����������Ă���Ԃ�true��Ԃ�
	bool getTrigger(GameInput input);	//�{�^���������ꂽ�u�Ԃ���true��Ԃ�
	bool getRelease(GameInput input);	//�{�^���������ꂽ�u�Ԃ���true��Ԃ�

protected:
	CustomInput();
	virtual ~CustomInput();

private:
	bool gameInputState[static_cast<int>(GameInput::GAME_INPUT_NUM)];		//�S�Ẵ{�^�����ƂɁA������Ă��邩�ǂ������L�^����ϐ�
	bool gameInputStateOld[static_cast<int>(GameInput::GAME_INPUT_NUM)];	//�O�t���[���ł̓��͏�Ԃ��L�^���邽�߂̕ϐ�

};

