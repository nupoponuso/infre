#include "Scene_Game.h"
#include "RM.h"
#include "MeshM.h"
#include "Enemy_1.h"
#include "input.h"
#include "F_lib/include/Light.h"
#include "item.h"

SceneGame::SceneGame(F_lib_Fremworker::ResourceManager * _ResouseManeger)
	: SceneBase(_ResouseManeger)
{
	Text = _ResouseManeger->meshM->getText();
	_ResouseManeger->meshM->getCamera()->setangle(XMFLOAT3(-89.99f, 0, 0));
	
	fild = _ResouseManeger->meshM->getModel(1);
	elist  = new MoverList();
	eblist = new MoverList();
	blist  = new MoverList();
	Itemlist = new MoverList();

	initplayerdata datp;
	datp.R = _ResouseManeger;
	datp.enemyList = elist;
	datp.bulletList = blist;
	datp.enemybList = eblist;
	datp.itemList = Itemlist;

	p = new Player(datp);
	scenename = L"タイトル\nゲーム本編：gキー\n図鑑：bキー";
	hit = L"何かしらがプレイヤーに当たっている";

	InitItemData itemdata;
	itemdata.R = Resource;
	itemdata.pos = XMFLOAT3(50, 0, 0);

	initenemydata datEnemy;
	datEnemy.pos=XMFLOAT3(0,0,100);
	datEnemy.R = Resource;
	datEnemy.speed = 0.51;
	datEnemy.p = (Player*)p;
	datEnemy.mylist = elist;

	initEnemySpawner spawn;
	spawn.dat = datEnemy;
	spawn.list = elist;
	spawn.count = 2;
	spawn.spawnenum = 6;
	spawn.SpowneLen = 25;
	spawner = new EnemySpawner(spawn);

	//デバックで500体で負荷が出るリリース100000体で負荷が起きる60,000で運用か
	
}

void SceneGame::update()
{
	UpdateInput();

	if (GetKeyTrigger(VK_T))next = F_lib_Fremworker::Scene_title;
	else if (GetKeyTrigger(VK_B))next = F_lib_Fremworker::Scene_book;

	if (GetKeyTrigger(VK_P))
	{
		InitItemData itemdata;
		itemdata.R = Resource;
		itemdata.pos = XMFLOAT3(50, 0, 0);

		Itemlist->listPush(new ItemWepon(itemdata, Wepon_missilelunther));

	}

	p->update();
	spawner->update();
	elist->update();
	Itemlist->update();
	blist->update();

}

void SceneGame::Draw()
{

	s->reset();
	s->setSize(500);
	s->RDraw(false);

	fild->RDraw();
	elist->Draw();
	Itemlist->Draw();
	p->Draw();
	blist->Draw();
	Text->draw(scenename);
	

}
