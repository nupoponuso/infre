//-------------------------------------------
//
//	FPS�̊Ǘ��N���X�N���X 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//�C���N���[�h
#include "Fpsmaneger.h"


namespace F_lib_Fremworker
{
	//�R���X�g���N�^
	//������
	Fpsmaneger::Fpsmaneger()
	{
		timeBeginPeriod(1);
		ExecLastTime = fpsLastTime = timeGetTime();
		CurrentTime = Framecount = 0;
	}


	//�f�X�g���N�^
	Fpsmaneger::~Fpsmaneger()
	{
		timeEndPeriod(1);
	}


	//update�֐�
	//FPS�̐���A�c��
	bool Fpsmaneger::update()
	{
		CurrentTime = timeGetTime();

		if ((CurrentTime - fpsLastTime) >= 500)
		{
			countFps = Framecount * 1000 / (CurrentTime - fpsLastTime);
			fpsLastTime = CurrentTime;
			Framecount = 0;

		}

		if ((CurrentTime - ExecLastTime) >= (1000 / 60))
		{
			ExecLastTime = CurrentTime;
			return true;
		}

		return false;
	}

}