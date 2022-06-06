#include "EnemySpawner.h"

#include "Enemy_1.h"
#include <random>
#include "Player.h"

EnemySpawner::EnemySpawner(initEnemySpawner _dat) : count(0), countmax(_dat.count * 60)
, SpawneData(_dat.dat), list(_dat.list), spawnenum(_dat.spawnenum)
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
	F_lib_Mover::Mover* m;

	for (int i = 0; i < spawnenum; i++)
	{
		float angle = rand100(mt);

		SpawneData.pos = SpawneData.p->getthisposition();
		SpawneData.pos.x += 100 * sindeg(angle);
		SpawneData.pos.z += 100 * cosdeg(angle);

		m = new Enemy_1(SpawneData);

		list->listPush(m);

	}

}
