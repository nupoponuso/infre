#include "Enemy.h"

#include "RM.h"

using namespace F_lib_Mover;
using namespace F_lib_Render;

Enemy::Enemy(initenemydata _dat) : Mover(_dat.R, XMFLOAT3(), _dat.speed), bulletlist(_dat.bulletlist), p(_dat.p)
{
	col = new Colision_2D(Colision_2D::Col_crecle);
	col->getColdata()->size.x = 1;

	Position = _dat.pos;
	mesh = _dat.R->meshM->getModel(2);

}

void Enemy::update()
{
	move();

}

void Enemy::Draw()
{

	mesh->setPosition(Position);
	mesh->RDraw();

}

void Enemy::terhit(Mover *)
{
}

void Enemy::herhit(Mover *_m)
{

	if (_m->getmyid() == mover_bullet)
		Alive = false;


}

F_lib_Mover::Colision_2D * Enemy::getcol()
{
	col->getColdata()->pos = XMFLOAT2(Position.x, Position.z);

	return col;
}
