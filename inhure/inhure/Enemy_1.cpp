#include "Enemy_1.h"

#include "Player.h"

Enemy_1::Enemy_1(initenemydata _dat) : Enemy(_dat)
{

}

void Enemy_1::move()
{
	XMFLOAT2 thisposold = XMFLOAT2(p->getthisposition().x, p->getthisposition().z);
		thisposold.x = thisposold.x - Position.x;
		thisposold.y = thisposold.y - Position.z;

	angle.y = atan2(thisposold.x, thisposold.y)* 180.0f / 3.14f;

	Position.x += sindeg(angle.y);
	Position.z += cosdeg(angle.y);

}
