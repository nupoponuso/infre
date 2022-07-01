//
//
//


#pragma once

//インクルード
#include "Enemy.h"


//エリアで出現する敵
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

