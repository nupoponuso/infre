//-----------------------------------------
//	
//	ゲーム内のエリア　| gameArea.cpp |
//	
//		auhor: hujioka tomoya
//
//		6月29日作成
//
//-----------------------------------------


//インクルード
#include "gameArea.h"

#include "Player.h"
#include "Boss.h"
#include "AreaEnemySpawner.h"
#include "BossArea.h"


//コンストラクタ
GameArea::GameArea(InitGameArea _data) :p(_data.p), R(_data.R), elist(_data.elist), eblist(_data.eblist), Position(_data.pos), Active(true)
{
	enemyData.p = p;
	enemyData.R = R;
	enemyData.pos = XMFLOAT3(0, 0, 100);
	enemyData.speed = 0.51;
	enemyData.bulletlist = eblist;
	enemyData.mylist = elist;

	spdata.R = R;
	spdata.list = elist;
	spdata.count = 2;
	spdata.spawnenum = 6;
	spdata.SpowneLen = 25;
	spdata.dat = enemyData;
	spawner = new AreaEnemySpawner(spdata,this);

	size = 150;

	col = new F_lib_Mover::Colision_2D(F_lib_Mover::Colision_2D::Col_Box);
	col->getColdata()->size.x = col->getColdata()->size.y = size / 2;
	col->getColdata()->pos = Position;

	b = R->meshM->getBillbord();

	InitBossData bossdata;
	bossdata.Pos = XMFLOAT3(Position.x,10, Position.y);
	bossdata.R = R;
	boss = new BossArea(bossdata);

}


//デストラクタ
GameArea::~GameArea()
{
}


//　更新処理
//　プレイヤーがエリア範囲に入っているときの処理
void GameArea::Update()
{

	isUpdate = col->ishit(p->getcol());
	if (!isUpdate) return;

	spawner->update();

	if (boss != nullptr)
	{
		boss->Update();
		if (!boss->Alive)
			Active = false;
	
	}
	

}


//　描画処理
void GameArea::Draw()
{
	b->reset();
	b->setPosition(XMFLOAT3(Position.x, -30, Position.y));
	b->setSize(size, size);
	b->setColor(1, 0, 0);
	b->setalph(0.6);
	b->RDraw();

	if (boss->Alive)
		boss->Draw();

}
