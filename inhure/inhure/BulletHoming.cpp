#include "BulletHoming.h"


BulletHoming::BulletHoming(inithpmingbulletdata _dat) : Bullet(_dat.data), maxrotangle(_dat.maxrotangle), terget(_dat.terget)
{
}

void BulletHoming::move()
{
	if (terget != nullptr)
	{
		if (!terget->Alive) 
		{
			terget = nullptr;
			return;

		}

		float rotangle;

		rotangle = F_lib_Mover::getLockAngle_2D(XMFLOAT2(this->getPosition().x, this->getPosition().z), XMFLOAT2(terget->getPosition().x, terget->getPosition().z));
		rotangle -= Angle.y;

		if (-maxrotangle > rotangle || rotangle > maxrotangle)
			rotangle = (rotangle > 0) ? maxrotangle : -maxrotangle;
	
		Angle.y += rotangle;

	}

	Bullet::move();

}

