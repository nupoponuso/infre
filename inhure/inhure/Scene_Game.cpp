#include "Scene_Game.h"
#include "RM.h"
#include "MeshM.h"
#include "Enemy_1.h"
#include "input.h"
#include "F_lib/include/Light.h"

SceneGame::SceneGame(F_lib_Fremworker::ResourceManager * _ResouseManeger)
	: SceneBase(_ResouseManeger)
{
	Text = _ResouseManeger->meshM->getText();
	_ResouseManeger->meshM->getCamera()->setangle(XMFLOAT3(-89.99f, 0, 0));
	
	fild = _ResouseManeger->meshM->getModel(1);
	elist  = new MoverList();
	eblist = new MoverList();
	blist  = new MoverList();

	initplayerdata datp;
	datp.R = _ResouseManeger;
	datp.enemylist = elist;
	datp.buletlist = blist;
	datp.ebuletlist = eblist;

	p = new Player(datp);
	scenename = L"タイトル\nゲーム本編：gキー\n図鑑：bキー";
	hit = L"何かしらがプレイヤーに当たっている";


	Mover2D* m;
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
	spawn.spawnenum = 12;
	spawner = new EnemySpawner(spawn);


	//デバックで500体で負荷が出るリリース100000体で負荷が起きる60,000で運用か
	
}

void SceneGame::update()
{
	UpdateInput();

	if (GetKeyTrigger(VK_T))next = F_lib_Fremworker::Scene_title;
	else if (GetKeyTrigger(VK_B))next = F_lib_Fremworker::Scene_book;

	p->update();
	spawner->update();
	elist->update();
	
	blist->update();

}

void SceneGame::Draw()
{

	s->reset();
	s->setSize(500);
	s->RDraw(false);

	fild->RDraw();
	elist->Draw();
	p->Draw();
	blist->Draw();
	Text->draw(scenename);
	

}
