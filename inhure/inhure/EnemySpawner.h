#pragma once

#include "F_lib/include/moverManeger.h"
#include "Enemy.h"

struct initEnemySpawner
{
	F_lib_Fremworker::ResourceManager* R;
	F_lib_Mover::moverList* list;

	int count;

};

class EnemySpawner
{
public:
	EnemySpawner(initEnemySpawner);

	void update();

private:

	void Spawne();

	F_lib_Mover::moverList* list;
	initenemydata SpawneData;
	int count,countmax;

};

