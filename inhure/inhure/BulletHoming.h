#pragma once
#include "Bullet.h"

struct inithpmingbulletdata
{
	initbulletdata data;
	Mover2D* terget;
	int maxrotangle;

};

class BulletHoming :public Bullet
{
public:
	BulletHoming(inithpmingbulletdata);

private:
	void move();

	Mover2D* terget;
	int maxrotangle;

};

