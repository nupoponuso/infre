#include "Wepon.h"

using namespace F_lib_Mover;

Wepon::Wepon(initWepondata _dat) :Mover2D(_dat.R), enemylist(_dat.EnemyList), p(_dat.p)
{
	Position = _dat.pos;
	Position.y - 10;
	a2 = _dat.pangle;

}

void Wepon::update()
{
	if (!Alive) return;

	move();

	ThisAtack();

}

void Wepon::move()
{
	ppos = p->getPosition();

	ppos.x += 7 * sindeg(p->getAngle().y - a2);
	ppos.z += 7 * cosdeg(p->getAngle().y - a2);

	thisposold = XMFLOAT2(ppos.x - Position.x, ppos.z - Position.z);

	if (thisposold.x*thisposold.x + thisposold.y*thisposold.y > 15)
		 nowspeed = speed;
	else nowspeed = speed * 0.2f;

	pangle = atan2(thisposold.x, thisposold.y);
	pangle = pangle * 180.0f / 3.14f;
	Angle.y = pangle;

	a2 += 4;
	Position.x += nowspeed * sindeg(Angle.y);
	Position.z += nowspeed * cosdeg(Angle.y);
	

}

void Wepon::ThisAtack()
{
	if (cooltime)
	{
		if (cooltimeNow <= 0)
		{
			cooltime = false;
			cooltimeNow = cooltimeMax;

		}
		else cooltimeNow--;

	}
	else
	{
		if (countNow <= 0)
		{
			cooltime = true;
			countNow = countMax;

		}
		else countNow--;

	}

}
