#include "Enemy.h"

#include "RM.h"
#include "F_lib/include/mover.h"

using namespace F_lib_Mover;
using namespace F_lib_Render;

Enemy::Enemy(initenemydata _dat) : Mover(_dat.R, XMFLOAT3(), _dat.speed), bulletlist(_dat.bulletlist), p(_dat.p)
{
	myid = mover_enemy;
	mylist = _dat.mylist;
	col = new Colision_2D(Colision_2D::Col_crecle);
	col->getColdata()->size.x = 1;

	Position = _dat.pos;
	mesh = _dat.R->meshM->getModel(2);

}

void Enemy::update()
{
	if (hp < 0)Alive = false;

	move();

	if (mylist->getlistNum() > 0)
		mylist->Ishit(this);
}

void Enemy::Draw()
{

	mesh->setPosition(Position);
	mesh->RDraw();

}

void Enemy::terhit(Mover * _m)
{

	switch (_m->getmyid())
	{
	
	case mover_enemy:
		
		float len, angle;
		len = col->getColdata()->size.x*0.9f;
		XMFLOAT2 thispos = XMFLOAT2(_m->getthisposition().x, _m->getthisposition().z);
		thispos.x = thispos.x - Position.x;
		thispos.y = thispos.y - Position.z;
		angle = atan2(thispos.x, thispos.y)* 180.0f / 3.14f;

		Position.x += len * sindeg(-angle);
		Position.z += len * cosdeg(-angle);

		break;
	}
}

void Enemy::herhit(Mover *_m)
{
	switch (_m->getmyid())
	{
	case mover_bullet:
		hp -= _m->getatack();

		break;

	case mover_enemy:

		float len, angle;
		len = col->getColdata()->size.x*0.1f;
		XMFLOAT2 thispos = XMFLOAT2(_m->getthisposition().x, _m->getthisposition().z);
		thispos.x = thispos.x - Position.x;
		thispos.y = thispos.y - Position.z;
		angle = atan2(thispos.x, thispos.y)* 180.0f / 3.14f;
		
		Position.x += len * sindeg(-angle);
		Position.z += len * cosdeg(-angle);
		break;
	}
	 
}

F_lib_Mover::Colision_2D * Enemy::getcol()
{
	col->getColdata()->pos = XMFLOAT2(Position.x, Position.z);

	return col;
}
