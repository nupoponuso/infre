

#pragma once

//�C���N���[�h
#include "EnemySpawner.h"


//�@AreaEnemySpawner�N���X�@�p��->EnemySpawner
//�@gameArea�ŏo�Ă���G�𐶐����邽�߂̃N���X
class AreaEnemySpawner : public EnemySpawner
{
public:
	AreaEnemySpawner(initEnemySpawner, class GameArea*);

protected:
	void PositionSet()	   override;
	Mover2D* CreateEnemy() override;

	class GameArea* area;

};

