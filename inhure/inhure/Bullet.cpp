#include "Bullet.h"

#include "RM.h"

using namespace F_lib_Mover;


Bullet::Bullet(initbulletdata _dat) :Mover(_dat.R, XMFLOAT3(0, _dat.angle, 0), _dat.speed),atacklist(_dat.atacklist)
{
	atack = _dat.atack;
	myid = mover_bullet;
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

	mesh->setangle(angle);
	mesh->setPosition(Position);
	mesh->RDraw();

}

void Bullet::terhit(Mover *)
{
	hit = true;
	Alive = false;

}

F_lib_Mover::Colision_2D * Bullet::getcol()
{
	col->getColdata()->pos = XMFLOAT2(Position.x, Position.z);
	return col;
}

void Bullet::move()
{

	Position.x += speed * sindeg(angle.y);
	Position.z += speed * cosdeg(angle.y);

	count++;

	if (count > 300) Alive = false;

}

void Bullet::myhit()
{

	if (!atacklist->Ishit(this)) hit = false;

}
