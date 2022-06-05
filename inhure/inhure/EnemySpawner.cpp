#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(initEnemySpawner _dat) : count(0), countmax(_dat.count)
{
}

void EnemySpawner::update()
{
	if (count > countmax)
	{
		Spawne();
		count = 0;

	}
	else count++;


}

void EnemySpawner::Spawne()
{
}
