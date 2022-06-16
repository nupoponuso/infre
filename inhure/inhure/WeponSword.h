#pragma once
#include "Wepon.h"

#include "F_lib/include/Mesh_billbord.h"

class WeponSword : public Wepon
{
public:
	WeponSword(initWepondata);

	void Draw();
	void terhit(Mover2D*);
	F_lib_Mover::Colision_2D* getcol();

private:
	void move();
	void ThisAtack();

	F_lib_Render::Mesh_billbord* b;
	XMFLOAT2 sPos;
	float srdAngle;
};

