#pragma once

#include "Wepon.h"

#include "Bullet.h"


class Wepon_MissileLunther :public Wepon
{
public:
	Wepon_MissileLunther(initWepondata,MoverList*);

	void Draw();


private:
	void ThisAtack();

	initbulletdata dat;
	MoverList* buletlist;

};

