//-------------------------------------------
//
//	FPSの管理クラスクラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//インクルード
#include "comon.h"
#include "singlton.h"


namespace F_lib_Fremworker
{
	//Fpsmanegerクラス　継承->Singleton
	//クラスメンバ
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