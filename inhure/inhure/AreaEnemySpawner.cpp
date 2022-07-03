

//インクルード
#include "AreaEnemySpawner.h"

#include "EnemyArea.h"
#include "gameArea.h"
#include <random>


//コンストラクタ
//
AreaEnemySpawner::AreaEnemySpawner(initEnemySpawner _dat, GameArea * _a) :EnemySpawner(_dat), area(_a)
{
}


//
//
void AreaEnemySpawner::PositionSet()
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rand(-area->getSize() / 2, area->getSize() / 2);

	SpawneData.pos.x = area->getPosition().x + rand(mt);
	SpawneData.pos.z = area->getPosition().y + rand(mt);

}

//
//
Mover2D * AreaEnemySpawner::CreateEnemy()
{
	return new EnemyArea(SpawneData, area);
}
