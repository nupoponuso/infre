#include "Enemy_1.h"

#include "Player.h"
#include "input.h"

Enemy_1::Enemy_1(initenemydata _dat) : Enemy(_dat)
{

}

void Enemy_1::move()
{
	ismove = true;
	
	if (GetKeyPress(VK_UP))
	{
		if (GetKeyPress(VK_LEFT))angle.y = -45;
		else if (GetKeyPress(VK_RIGHT)) angle.y = 45;
		else angle.y = 0;
	
	}
	else if (GetKeyPress(VK_DOWN))
	{
		if (GetKeyPress(VK_LEFT)) angle.y = -135;
		else if (GetKeyPress(VK_RIGHT)) angle.y = 135;
		else angle.y = 180;
	
	}
	else
	{
		if (GetKeyPress(VK_LEFT)) angle.y = -90;
		else if (GetKeyPress(VK_RIGHT)) angle.y = 90;
		else ismove = false;
	
	}

	//XMFLOAT2 thisposold = XMFLOAT2(p->getthisposition().x, p->getthisposition().z);
	//	thisposold.x = thisposold.x - Position.x;
	//	thisposold.y = thisposold.y - Position.z;
	//
	//angle.y = atan2(thisposold.x, thisposold.y)* 180.0f / 3.14f;

	if (ismove)
	{
		Position.x += sindeg(angle.y);
		Position.z += cosdeg(angle.y);
	
	}

}
