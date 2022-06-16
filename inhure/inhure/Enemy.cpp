#include "Enemy.h"

#include "RM.h"
#include "F_lib/include/mover.h"

using namespace F_lib_Mover;
using namespace F_lib_Render;

Enemy::Enemy(initenemydata _dat) : Mover2D(_dat.R), bulletList(_dat.bulletlist), p(_dat.p)
{
	speed = _dat.speed;
	Myid = mover_enemy;
	myList = _dat.mylist;
	col = new Colision_2D(Colision_2D::Col_crecle);
	col->getColdata()->size.x = 1;


	Position = _dat.pos;
	mesh = _dat.R->meshM->getModel(2);

}

void Enemy::update()
{
	if (hp < 0)Alive = false;

	move();
	myAtack();

	if (myList->getlistNum() > 0)
		myList->Ishit(this);
}

void Enemy::Draw()
{

	mesh->setPosition(Position);
	mesh->RDraw();

}

void Enemy::terhit(Mover2D * _m)
{

	switch (_m->getMyid())
	{
	
	case mover_enemy:
		
		float len, angle;
		len = col->getColdata()->size.x*0.9f;
		
		angle = F_lib_Mover::getLockAngle_2D(XMFLOAT2(this->getPosition().x, this->getPosition().y), XMFLOAT2(_m->getPosition().x, _m->getPosition().y));

		Position.x += len * sindeg(-angle);
		Position.z += len * cosdeg(-angle);

		break;
	}
}

void Enemy::herhit(Mover2D *_m)
{
	switch (_m->getMyid())
	{
	case mover_bullet:
	//	hp -= _m->getatack();

		break;

	case mover_enemy:

		float len, angle;
		len = col->getColdata()->size.x*0.1f;
		angle = F_lib_Mover::getLockAngle_2D(XMFLOAT2(this->getPosition().x, this->getPosition().y), XMFLOAT2(_m->getPosition().x, _m->getPosition().y));

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
