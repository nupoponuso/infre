#include "BulletHoming.h"


BulletHoming::BulletHoming(inithpmingbulletdata _dat) : Bullet(_dat.data), maxrotangle(_dat.maxrotangle)
{
}

void BulletHoming::move()
{
	float rotangle;
	
	rotangle = F_lib_Mover::getLockAngle_2D(XMFLOAT2(this->getPosition().x, this->getPosition().y), XMFLOAT2(terget->getPosition().x, terget->getPosition().y));

	if (-maxrotangle < rotangle && rotangle < maxrotangle) Angle.y = rotangle;
	else rotangle = (rotangle > maxrotangle) ? maxrotangle : -maxrotangle;

	Bullet::move();

}

