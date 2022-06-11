#include "Enemy_1.h"

#include "Player.h"
#include "input.h"

Enemy_1::Enemy_1(initenemydata _dat) : Enemy(_dat)
{
	//hp = 20;
}

void Enemy_1::move()
{
	ismove = true;

	//if (GetKeyPress(VK_UP))
	//{
	//	if (GetKeyPress(VK_LEFT))angle.y = -45;
	//	else if (GetKeyPress(VK_RIGHT)) angle.y = 45;
	//	else angle.y = 0;
	//
	//}
	//else if (GetKeyPress(VK_DOWN))
	//{
	//	if (GetKeyPress(VK_LEFT)) angle.y = -135;
	//	else if (GetKeyPress(VK_RIGHT)) angle.y = 135;
	//	else angle.y = 180;
	//
	//}
	//else
	//{
	//	if (GetKeyPress(VK_LEFT)) angle.y = -90;
	//	else if (GetKeyPress(VK_RIGHT)) angle.y = 90;
	//	else ismove = false;
	//
	//}

	if (!hit)
	{
		
		Angle.y = F_lib_Mover::getLockAngle_2D(XMFLOAT2(this->getPosition().x, this->getPosition().y), XMFLOAT2(p->getPosition().x, p->getPosition().y));

		if (ismove && !p->getcol()->ishit(this->getcol()))
		{
			Position.x += speed * sindeg(Angle.y);
			Position.z += speed * cosdeg(Angle.y);

		}

	}


}
