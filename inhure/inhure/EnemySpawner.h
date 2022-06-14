#pragma once

#include "MoverList.h"
#include "Enemy.h"

struct initEnemySpawner
{
	F_lib_Fremworker::ResourceManager* R;
	MoverList* list;
	initenemydata dat;

	int count, spawnenum;
	float SpowneLen;
	initEnemySpawner()
	{
		spawnenum = 1;
		SpowneLen = 100;
	}

};

class EnemySpawner
{
public:
	EnemySpawner(initEnemySpawner);

	void update();

private:

	void Spawne();

	MoverList* list;
	initenemydata SpawneData;
	int count,countmax,spawnenum;
	float SpowneLen;

};

