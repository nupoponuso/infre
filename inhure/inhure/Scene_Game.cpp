
//インクルード
#include "Scene_Game.h"
#include "RM.h"
#include "MeshM.h"
#include "Enemy_1.h"
#include "input.h"
#include "F_lib/include/Light.h"
#include "item.h"
#include "gameArea.h"
#include "ItemFactory.h"
#include "UIPlayer.h"

//定数宣言
#define AREAPOS (110)


//
//
SceneGame::SceneGame(F_lib_Fremworker::ResourceManager * _ResouseManeger)
	: SceneBase(_ResouseManeger)
{
	Text = _ResouseManeger->meshM->getText();
	_ResouseManeger->meshM->getCamera()->setangle(XMFLOAT3(-89.99f, 0, 0));
	Resource->TM->loadTex();
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

	itemfactory = new ItemFactory(Resource, Itemlist);

	InitGameArea areadata;
	areadata.eblist = eblist;
	areadata.elist = elist;
	areadata.p = dynamic_cast<Player*>(p);
	areadata.R = Resource;
	areadata.factry = itemfactory;

	XMFLOAT2 areapos;

	for (int i = 0; i < 4; i++)
	{
		areapos.x = ((i % 2 == 0) ? 1 : -1) * AREAPOS;
		areapos.y = ((i < 2) ? 1 : -1)* AREAPOS;
		areadata.pos = areapos;
		area[i] = new GameArea(areadata);

	}

	pui = new UIPlayer(_ResouseManeger, dynamic_cast<Player*>( p));
	b = Resource->meshM->getBillbord();

}


//
//
void SceneGame::update()
{

	if (GetKeyTrigger(VK_T))next = F_lib_Fremworker::Scene_title;
	else if (GetKeyTrigger(VK_B))next = F_lib_Fremworker::Scene_book;

	for (int i = 0; i < 4; i++)
		area[i]->Update();

	//if (GetKeyTrigger(VK_C))
		 p->Update();
	//else p->update();

	elist->update();
	Itemlist->update();
	blist->update();

	pui->Update();
}


//
//
void SceneGame::Draw()
{
	b->reset();
	b->setColor(0, 0, 0);
	b->setPosition(XMFLOAT3(0, -40, 0));
	b->setSize(1000);
	b->RDraw();

	for (int i = 0; i < 4; i++)
		area[i]->Draw();

	elist->Draw();
	Itemlist->Draw();
	p->Draw();
	blist->Draw();
	pui->Draw();
	
}
