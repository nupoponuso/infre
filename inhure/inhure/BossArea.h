//-----------------------------------------------------
//
//		�G���A�{�X�N���X�@|�@BossArea.cpp�@|
//
//		auhor: hujioka tomoya
//
//		6��30���쐬
//
//-----------------------------------------------------

#pragma once

//�C���N���[�h
#include "Boss.h"


//�@BossArea�N���X�@�p����Boss
//�@�G���A�ŏo������N���X
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

