//
//
//


#pragma once

//�C���N���[�h
#include "Enemy.h"


//�G���A�ŏo������G
class EnemyArea : public Enemy
{
public:
	EnemyArea(initenemydata _dat, class GameArea*);

	void Update();

protected:
	void move();
	void myAtack();

	class GameArea* area;

};

