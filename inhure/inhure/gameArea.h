//-----------------------------------------
//
//	ゲーム内のエリア　| gameArea.cpp |
//
//		auhor: hujioka tomoya
//
//		6月29日作成
//
//-----------------------------------------

#pragma once

//インクルード
#include "Colision.h"
#include "MoverList.h"
#include "Mesh_billbord.h"
#include "ResourceManager.h"
#include "EnemySpawner.h"
#include "Enemy.h"


//初期化用構造体
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

	void Update();	//更新処理
	void Draw();	//描画処理

	bool getActive()   { return Active; }
	bool getIsUpdate() { return isUpdate; }
	F_lib_Mover::Colision_2D* getCol() { return col; }

protected:
	
	F_lib_Fremworker::ResourceManager* R;
	class Player* p;				//プレイヤー
	class EnemySpawner* spawner;	//スポナー
	class Boss* boss;
	F_lib_Mover::Colision_2D* col;	//エリアエリア当たり判定
	F_lib_Render::Mesh_billbord* b;
	MoverList*	elist,* eblist;		//敵リスト、敵弾リスト
	initEnemySpawner spdata;
	initenemydata enemyData;

	XMFLOAT2 Position;
	float size;
	bool Active,isUpdate;

};

