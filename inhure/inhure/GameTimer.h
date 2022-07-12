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

	void restart();		// �v���J�n�b��ۑ�
	double elapsed();	// ���X�^�[�g����̕b����Ԃ�

	void Update();
	void Draw();	// �������e�̓e�X�g�i�K

	bool IsPause();

private:
	bool Pause;			// �ꎞ��~ true:���Ă���/false:���Ă��Ȃ�
	DWORD CurrentTime;	// �v�Z�p���ݎ���
	double TimerCount;	// �o�͗p�o�ߎ���
#ifdef _DEBUG
	F_lib_Render::D2DTextParams* CountText;	// �f�o�b�O�p�J�E���g�\��
#endif // _DEBUG
};

