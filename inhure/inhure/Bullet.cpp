#include "Bullet.h"

#include "RM.h"

using namespace F_lib_Mover;


Bullet::Bullet(initbulletdata _dat) :Mover2D(_dat.R),atacklist(_dat.atacklist)
{
	Angle.y = _dat.angle;
	speed = _dat.speed;
	atack = _dat.atack;
	Myid = mover_bullet;
	Position = _dat.pos;
	col = new Colision_2D(Colision_2D::Col_crecle);
	col->getColdata()->size.x = _dat.size;

	mesh = _dat.R->meshM->getModel(3);
	hit = false;

}

void Bullet::update()
{
	if (!Alive) 
		return;

	move();

	myhit();
	
}

void Bullet::Draw()
{

	mesh->setangle(Angle);
	mesh->setPosition(Position);
	mesh->RDraw();

}

void Bullet::terhit(Mover2D * _m)
{
	hit = true;
	Alive = false;

	_m->Alive = false;

}

F_lib_Mover::Colision_2D * Bullet::getcol()
{
	col->getColdata()->pos = XMFLOAT2(Position.x, Position.z);
	return col;
}

void Bullet::move()
{

	Position.x += speed * sindeg(Angle.y);
	Position.z += speed * cosdeg(Angle.y);

	count++;

	if (count > 300) Alive = false;

}

void Bullet::myhit()
{

	if (!atacklist->Ishit(this)) hit = false;

}
