#pragma once

#include "EnemySpawner.h"


class AreaEnemySpawner : public EnemySpawner
{
public:
	AreaEnemySpawner(initEnemySpawner, class GameArea*);

protected:

	Mover2D* CreateEnemy() override;

	class GameArea* area;
};

