#include "AreaEnemySpawner.h"

#include "EnemyArea.h"

AreaEnemySpawner::AreaEnemySpawner(initEnemySpawner _dat, GameArea * _a) :EnemySpawner(_dat), area(_a)
{
}

Mover2D * AreaEnemySpawner::CreateEnemy()
{
	return new EnemyArea(SpawneData, area);
}
