

#include "EnemyArea.h"
#include "gameArea.h"
#include "Player.h"

EnemyArea::EnemyArea(initenemydata _dat, GameArea * _a) :Enemy(_dat), area(_a)
{
	ep = 1;
	hp = 30;
}

void EnemyArea::Update()
{
	if (!area->getActive())
		Alive = false;

	Enemy::Update();

}

void EnemyArea::move()
{
	ismove = (area->getIsUpdate());

	if (!hit && !isAtack)
	{
		if(!ismove)
		{
			if (!area->getCol()->ishit(this->getcol()))
			{
				ismove = true;
				Angle.y = F_lib_Mover::getLockAngle_2D(XMFLOAT2(this->getPosition().x, this->getPosition().z), area->getCol()->getColdata()->pos);

			}

		}
		else Angle.y = F_lib_Mover::getLockAngle_2D(XMFLOAT2(this->getPosition().x, this->getPosition().z), XMFLOAT2(p->getPosition().x, p->getPosition().z));

		if (ismove && !p->getcol()->ishit(this->getcol()))
		{
			Position.x += speed * sindeg(Angle.y);
			Position.z += speed * cosdeg(Angle.y);

		}
		

	}

}

void EnemyArea::myAtack()
{
}
