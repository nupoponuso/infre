//-------------------------------------------
//
//	FPSの管理クラスクラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//インクルード
#include "Fpsmaneger.h"


namespace F_lib_Fremworker
{
	//コンストラクタ
	//初期化
	Fpsmaneger::Fpsmaneger()
	{
		timeBeginPeriod(1);
		ExecLastTime = fpsLastTime = timeGetTime();
		CurrentTime = Framecount = 0;
	}


	//デストラクタ
	Fpsmaneger::~Fpsmaneger()
	{
		timeEndPeriod(1);
	}


	//update関数
	//FPSの制御、把握
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