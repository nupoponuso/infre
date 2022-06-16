#pragma once
#include "Wepon.h"
class WeponBoomerang : public Wepon
{
public:
	WeponBoomerang(initWepondata);

	void Draw();
	void terhit(Mover2D*);
	F_lib_Mover::Colision_2D* getcol();

private:
	void move();
	void ThisAtack();
	F_lib_Render::Mesh_billbord* b;

	bool isMove;
	float shotAngle;

};

