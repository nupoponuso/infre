#pragma once
#include "Bullet.h"

struct inithpmingbulletdata
{
	initbulletdata data;
	F_lib_Mover::Mover* terget;
	int maxrotangle;

};

class BulletHoming :public Bullet
{
public:
	BulletHoming(inithpmingbulletdata);

private:
	void move();

	F_lib_Mover::Mover* terget;
	int maxrotangle;

};

