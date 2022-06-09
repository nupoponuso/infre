#include "BulletHoming.h"


BulletHoming::BulletHoming(inithpmingbulletdata _dat) : Bullet(_dat.data), maxrotangle(_dat.maxrotangle)
{
}

void BulletHoming::move()
{
	float rotangle;
	XMFLOAT2 thispos = XMFLOAT2(terget->getthisposition().x, terget->getthisposition().z);
	thispos.x = thispos.x - Position.x;
	thispos.y = thispos.y - Position.z;
	rotangle = atan2(thispos.x, thispos.y)* 180.0f / 3.14f;

	if (-maxrotangle < rotangle && rotangle < maxrotangle) angle.y = rotangle;
	else rotangle = (rotangle > maxrotangle) ? maxrotangle : -maxrotangle;

	Bullet::move();

}

