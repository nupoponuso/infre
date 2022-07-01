#include "Boss.h"
#include "MeshM.h"

Boss::Boss(InitBossData _dat) :Mover2D(_dat.R)
{
	Position = _dat.Pos;
	mesh = Resource->meshM->getModel(0);

}

void Boss::Update()
{
	if (stetas.hp < 0) Alive = false;

}

void Boss::Draw()
{

	mesh->setangle(Angle);
	mesh->setPosition(Position);
	mesh->RDraw();

}

void Boss::terhit(Mover2D *)
{
}

void Boss::herhit(Mover2D *)
{
}

F_lib_Mover::Colision_2D * Boss::getcol()
{
	return nullptr;
}
