#pragma once

#include "comon.h"
#include "D2DText.h"

class GameTimer
{
public:
	GameTimer();
	~GameTimer();

	void restart();		// �v���J�n�b��ۑ�
	double elapsed();	// ���X�^�[�g����̕b����Ԃ�

	void Update();
	void Draw();	// �������e�̓e�X�g�i�K

	bool IsPause();

private:
	bool Pause;		// �ꎞ��~ true:���Ă���/false:���Ă��Ȃ�
	DWORD CurrentTime;
	double TimerCount;
	F_lib_Render::D2DText* CountText;
};

