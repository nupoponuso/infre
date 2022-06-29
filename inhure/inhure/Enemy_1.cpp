#include "Enemy_1.h"

#include "Player.h"
#include "input.h"

Enemy_1::Enemy_1(initenemydata _dat) : Enemy(_dat)
{
	hp = 20;
	ep = 10;
}

void Enemy_1::move()
{
	ismove = true;

	if (!hit && !isAtack)
	{	
		Angle.y = F_lib_Mover::getLockAngle_2D(XMFLOAT2(this->getPosition().x, this->getPosition().z), XMFLOAT2(p->getPosition().x, p->getPosition().z));

		if (ismove && !p->getcol()->ishit(this->getcol()))
		{
			Position.x += speed * sindeg(Angle.y);
			Position.z += speed * cosdeg(Angle.y);

		}

	}

	

}

void Enemy_1::myAtack()
{

	XMFLOAT2 thispos = XMFLOAT2(p->getPosition().x - Position.x, p->getPosition().z - Position.z);
	float len = thispos.x*thispos.x + thispos.y*thispos.y;

	isAtack = (len < 60.0f);

	//if(isAtack)
	//{
	//	
	//} 

	
}
