#include "Scene_Game.h"
#include "RM.h"
#include "MeshM.h"

#include "input.h"

SceneGame::SceneGame(F_lib_Fremworker::ResourceManager * _ResouseManeger)
	: SceneBase(_ResouseManeger)
{
	Text = _ResouseManeger->meshM->getText();
	scenename = L"�^�C�g��:t�L�[\n�Q�[���{��\n�}�ӁFb�L�[";

}

void SceneGame::update()
{
	UpdateInput();

	if (GetKeyTrigger(VK_T))next = F_lib_Fremworker::Scene_title;
	else if (GetKeyTrigger(VK_B))next = F_lib_Fremworker::Scene_book;

}

void SceneGame::Draw()
{
	Text->draw(scenename);

}
