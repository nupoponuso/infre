#include "WeponSword.h"

#include "F_lib/include/Mesh_billbord.h"

using namespace F_lib_Mover;

WeponSword::WeponSword(initWepondata _dat) :Wepon(_dat)
{
	atack = 100;
	b = _dat.R->meshM->getBillbord();

	col = new Colision_2D(Colision_2D::Col_Line);
	col->getColdata()->size.x = 10;

	speed = 2.11f;
	Position.y = -20;

}

void WeponSword::Draw()
{
	b->setPosition(Position);
	b->setSize(1,10);
	b->RDraw();
	

}

void WeponSword::terhit(Mover *_m)
{
	_m->addhp(-atack);

}

F_lib_Mover::Colision_2D * WeponSword::getcol()
{

	col->getColdata()->pos = XMFLOAT2(Position.x, Position.z);
	col->getColdata()->size = XMFLOAT2(Position.x, Position.z + 10);

	return col;
}

void WeponSword::ThisAtack()
{

	enemylist->Ishit(this);
	

}
