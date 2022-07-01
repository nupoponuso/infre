//-----------------------------------------------------
//
//		エリアボスクラス　|　BossArea.cpp　|
//
//		auhor: hujioka tomoya
//
//		6月30日作成
//
//-----------------------------------------------------

#pragma once

//インクルード
#include "Boss.h"


//　BossAreaクラス　継承→Boss
//　エリアで出現するクラス
class BossArea : public Boss
{
public:

	BossArea(InitBossData);
	virtual ~BossArea();

	void Update();
	void Draw();
	void terhit(Mover2D*);
	void herhit(Mover2D*);

	F_lib_Mover::Colision_2D* getcol();

protected:


};

