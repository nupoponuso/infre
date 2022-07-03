#include "EnemySpawner.h"

#include "Enemy_1.h"
#include "Enemy_2.h"
#include <random>
#include "Player.h"

EnemySpawner::EnemySpawner(initEnemySpawner _dat) : count(0), countmax(_dat.count * 60)
, SpawneData(_dat.dat), list(_dat.list), spawnenum(_dat.spawnenum), SpowneLen(_dat.SpowneLen)
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
	Mover2D* m;

	for (int i = 0; i < spawnenum; i++)
	{
		PositionSet();
		m = CreateEnemy();

		list->listPush(m);

	}

}

void EnemySpawner::PositionSet()
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rand(0, 360);

	float angle = (float)rand(mt);

	SpawneData.pos = SpawneData.p->getPosition();
	SpawneData.pos.x += SpowneLen * sindeg(angle);
	SpawneData.pos.z += SpowneLen * cosdeg(angle);

}

Mover2D * EnemySpawner::CreateEnemy()
{
	return  new Enemy_1(SpawneData);
}
