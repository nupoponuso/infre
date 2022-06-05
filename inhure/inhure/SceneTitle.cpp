#include "SceneTitle.h"
#include "RM.h"
#include "MeshM.h"

#include "input.h"



SceneTitle::SceneTitle(F_lib_Fremworker::ResourceManager * _R)
	: SceneBase(_R)
{
	Text = _R->meshM->getText();
	scenename = L"�^�C�g��\n�Q�[���{�ҁFg�L�[\n�}�ӁFb�L�[";
}

void SceneTitle::update()
{
	UpdateInput();

	if (GetKeyTrigger(VK_G))next = F_lib_Fremworker::Scene_game;
	else if (GetKeyTrigger(VK_B))next = F_lib_Fremworker::Scene_book;
}

void SceneTitle::Draw()
{
	Text->draw(scenename);

}
