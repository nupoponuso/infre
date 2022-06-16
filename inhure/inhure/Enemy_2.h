#pragma once
#include "Enemy.h"
class Enemy_2 : public Enemy
{
public:
	Enemy_2(initenemydata);

private:
	void move() { Position.z+=0.2f; }
	void myAtack() {};

};

