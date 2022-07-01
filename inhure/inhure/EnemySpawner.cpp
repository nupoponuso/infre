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
	std::random_device rnd;     
	std::mt19937 mt(rnd());     
	std::uniform_int_distribution<> rand100(0, 360);
	Mover2D* m;

	for (int i = 0; i < spawnenum; i++)
	{
		float angle = (float)rand100(mt);

		SpawneData.pos = SpawneData.p->getPosition();
		SpawneData.pos.x += SpowneLen * sindeg(angle);
		SpawneData.pos.z += SpowneLen * cosdeg(angle);

		m = CreateEnemy();

		list->listPush(m);

	}

}

Mover2D * EnemySpawner::CreateEnemy()
{
	return  new Enemy_1(SpawneData);
}
