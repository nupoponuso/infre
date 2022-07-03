

#pragma once

//インクルード
#include "EnemySpawner.h"


//　AreaEnemySpawnerクラス　継承->EnemySpawner
//　gameAreaで出てくる敵を生成するためのクラス
class AreaEnemySpawner : public EnemySpawner
{
public:
	AreaEnemySpawner(initEnemySpawner, class GameArea*);

protected:
	void PositionSet()	   override;
	Mover2D* CreateEnemy() override;

	class GameArea* area;

};

