//-------------------------------------------
//
//	FPS�̊Ǘ��N���X�N���X 
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//�C���N���[�h
#include "comon.h"
#include "singlton.h"


namespace F_lib_Fremworker
{
	//Fpsmaneger�N���X�@�p��->Singleton
	//�N���X�����o
	class Fpsmaneger : public Singleton <Fpsmaneger>
	{
	public:
		friend class Singleton< Fpsmaneger>;

		bool update();
		void Freamecount() { Framecount++; }

		int getFps() { return countFps; }

	protected:
		Fpsmaneger();
		virtual ~Fpsmaneger();

	private:
		DWORD ExecLastTime, fpsLastTime, CurrentTime, Framecount;
		int countFps;
	};

}