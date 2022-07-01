//-----------------------------------------
//
//	�Q�[�����̃G���A�@| gameArea.cpp |
//
//		auhor: hujioka tomoya
//
//		6��29���쐬
//
//-----------------------------------------

#pragma once

//�C���N���[�h
#include "Colision.h"
#include "MoverList.h"
#include "Mesh_billbord.h"
#include "ResourceManager.h"
#include "EnemySpawner.h"
#include "Enemy.h"


//�������p�\����
struct InitGameArea
{
	F_lib_Fremworker::ResourceManager* R;
	class Player* p;
	class EnemySpawner* spawner;
	MoverList*	elist, *eblist;
	XMFLOAT2 pos;

};

class GameArea
{
public:
	GameArea(InitGameArea);
	virtual ~GameArea();

	void Update();	//�X�V����
	void Draw();	//�`�揈��

	bool getActive()   { return Active; }
	bool getIsUpdate() { return isUpdate; }
	F_lib_Mover::Colision_2D* getCol() { return col; }

protected:
	
	F_lib_Fremworker::ResourceManager* R;
	class Player* p;				//�v���C���[
	class EnemySpawner* spawner;	//�X�|�i�[
	class Boss* boss;
	F_lib_Mover::Colision_2D* col;	//�G���A�G���A�����蔻��
	F_lib_Render::Mesh_billbord* b;
	MoverList*	elist,* eblist;		//�G���X�g�A�G�e���X�g
	initEnemySpawner spdata;
	initenemydata enemyData;

	XMFLOAT2 Position;
	float size;
	bool Active,isUpdate;

};

