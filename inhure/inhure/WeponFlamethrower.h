#pragma once
#include "Wepon.h"
#include "Bullet.h"

class WeponFlamethrower : public Wepon
{
public:
	WeponFlamethrower(initWepondata, MoverList*);

	void Draw();

private:
	void move();
	void ThisAtack();
	F_lib_Render::Mesh_billbord* b;
	initbulletdata dat;
	MoverList* buletlist;

};

