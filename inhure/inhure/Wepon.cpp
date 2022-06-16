#include "Wepon.h"

using namespace F_lib_Mover;

Wepon::Wepon(initWepondata _dat) :Mover2D(_dat.R), enemyList(_dat.EnemyList), p(_dat.p)
{
	Position = _dat.pos;
	Position.y -= 10;
	a2 = _dat.pangle;
	rotspeed = 4;

}

void Wepon::update()
{
	if (!Alive) return;

	move();

	ThisAtack();

}

void Wepon::move()
{
	pPos = p->getPosition();

	pPos.x += 7 * sindeg(p->getAngle().y - a2);
	pPos.z += 7 * cosdeg(p->getAngle().y - a2);

	thisPosOld = XMFLOAT2(pPos.x - Position.x, pPos.z - Position.z);

	if (thisPosOld.x*thisPosOld.x + thisPosOld.y*thisPosOld.y > 15)
		 nowSpeed = speed;
	else nowSpeed = speed * 0.2f;

	pAngle = atan2(thisPosOld.x, thisPosOld.y);
	pAngle = pAngle * 180.0f / 3.14f;
	Angle.y = pAngle;

	a2 += rotspeed;
	Position.x += nowSpeed * sindeg(Angle.y);
	Position.z += nowSpeed * cosdeg(Angle.y);
	

}

void Wepon::ThisAtack()
{
	if (coolTime)
	{
		if (cooltimeNow <= 0)
		{
			coolTime = false;
			cooltimeNow = cooltimeMax;

		}
		else cooltimeNow--;

	}
	else
	{
		if (countNow <= 0)
		{
			coolTime = true;
			countNow = countMax;

		}
		else countNow--;

	}

}
