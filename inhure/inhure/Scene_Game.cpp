#include "Scene_Game.h"
#include "RM.h"
#include "MeshM.h"
#include "Enemy.h"
#include "input.h"

SceneGame::SceneGame(F_lib_Fremworker::ResourceManager * _ResouseManeger)
	: SceneBase(_ResouseManeger)
{
	Text = _ResouseManeger->meshM->getText();
	_ResouseManeger->meshM->getCamera()->setangle(XMFLOAT3(-89.99f, 0, 0));

	fild = _ResouseManeger->meshM->getModel(1);
	elist = new F_lib_Mover::moverList();
	eblist = new F_lib_Mover::moverList();
	blist = new F_lib_Mover::moverList();

	initplayerdata datp;
	datp.R = _ResouseManeger;
	datp.enemylist = elist;
	datp.buletlist = blist;
	datp.ebuletlist = eblist;

	p = new Player(datp);
	scenename = L"�^�C�g��\n�Q�[���{�ҁFg�L�[\n�}�ӁFb�L�[";
	hit = L"�������炪�v���C���[�ɓ������Ă���";


	F_lib_Mover::Mover* m;
	initenemydata datEnemy;
	datEnemy.pos=XMFLOAT3();
	datEnemy.R = Resource;


	//�f�o�b�N��500�̂ŕ��ׂ��o�郊���[�X100000�̂ŕ��ׂ��N����60,000�ŉ^�p��
	//for (int i = 0; i < 20; i++)
	//{
	//	for (int j = 0; j < 20; j++)
	//	{
	//
	//		m = new Enemy(datEnemy);
	//		elist->listPush(m);
	//
	//		datEnemy.pos.x = 10 * j;
	//
	//	}
	//
	//	datEnemy.pos.z = 10 * i;
	//}
	
}

void SceneGame::update()
{
	UpdateInput();

	if (GetKeyTrigger(VK_T))next = F_lib_Fremworker::Scene_title;
	else if (GetKeyTrigger(VK_B))next = F_lib_Fremworker::Scene_book;

	p->update();
	elist->update();
	blist->update();

}

void SceneGame::Draw()
{

	s->reset();
	s->setSize(500);
	s->RDraw(false);

	//fild->RDraw();
	p->Draw();
	elist->Draw();
	blist->Draw();
	Text->draw(scenename);
	

}
