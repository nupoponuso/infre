#pragma once

#include "Wepon.h"

#include "Bullet.h"


class Wepon_MissileLunther :public Wepon
{
public:
	Wepon_MissileLunther(initWepondata,F_lib_Mover::moverList*);

	void Draw();


private:
	void ThisAtack();

	initbulletdata dat;
	F_lib_Mover::moverList* buletlist;

};

