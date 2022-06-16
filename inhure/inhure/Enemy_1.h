#pragma once
#include "Enemy.h"
class Enemy_1 : public Enemy
{
public:
	Enemy_1(initenemydata);
	
private:
	void move();
	void myAtack();
	bool ismove;

};

