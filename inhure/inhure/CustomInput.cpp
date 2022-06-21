#include "CustomInput.h"

#include "input.h"

using GI = GameInput;
#define SC_I(param) static_cast<int>(param)

CustomInput::CustomInput()
{
	// �����o�ϐ�������
	for (auto&& gs : gameInputState) {
		gs = false;
	}
	for (auto&& gs : gameInputStateOld) {
		gs = false;
	}
	// input.h�̏�����
	InitInput();
}

CustomInput::~CustomInput()
{
	// input.h�̌㏈��
	UninitInput();
}

void CustomInput::Update()
{
	// �e�f�o�C�X��update
	UpdateInput();

	// �{�^���̏�Ԃ��X�V����O�ɁA�ȑO�̏�Ԃ��L�^���Ă���
	for (int i = 0; i < SC_I(GI::GAME_INPUT_NUM); i++) {
		gameInputStateOld[i] = gameInputState[i];
	}

	/*	�P�P�̃Q�[���p���͂ɑ΂��āA
	*	�ǂ̃{�^���A�L�[��������Ă���Γ��͂��ꂽ�����ɂ��邩�������Ō��߂Ă��܂��B
	*/

	//�X�y�[�X�L�[���AJOYBUTTON1(���{�^������Ų)��
	//������Ă�����W�����v�{�^����������Ă��锻��ɂȂ�
	gameInputState[SC_I(GI::JUMP)] = 
		GetKeyPress(VK_SPACE) || 
		GetJoyButton(0, JOYBUTTON1);
	
	gameInputState[SC_I(GI::ATTACK)] = 
		GetKeyPress(VK_F) || 
		GetJoyButton(0, JOYBUTTON2);

	//�Ⴆ�΍U���{�^���ł��A�W�����v�{�^���ł��A�G���^�[�L�[�ł�
	//OK�{�^�����͂̈����ɂ������Ƃ��Ȃǂł����R�ɐݒ�ł��܂��B
	//����Ȋ����ňȉ��ȗ����
	gameInputState[SC_I(GI::OK)] =
		gameInputState[SC_I(GI::JUMP)] ||
		gameInputState[SC_I(GI::ATTACK)] ||
		GetKeyPress(VK_RETURN);
}

bool CustomInput::GetCustomInputPress(GameInput input)
{
	//�{�^�����������ςȂ� = ���݂̃t���[���ŉ�����Ă���
	return gameInputState[SC_I(input)] == true;
}

bool CustomInput::GetCustomInputTrigger(GameInput input)
{
	//�{�^���������ꂽ�u�� = ���݂̃t���[���ŉ�����Ă���{�P�t���[���O�ɂ͉�����Ă��Ȃ�
	return gameInputState[SC_I(input)] == true && gameInputStateOld[SC_I(input)] == false;
}

bool CustomInput::GetCustomInputRelease(GameInput input)
{
	//�{�^���������ꂽ�u�� = ���݂̃t���[���ł͗�����Ă���{�P�t���[���O�ɂ͉�����Ă���
	return gameInputState[SC_I(input)] == false && gameInputStateOld[SC_I(input)] == true;
}

#undef SC_I