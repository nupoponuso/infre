#include "Scene_Corection.h"
#include "RM.h"
#include "MeshM.h"

#include "input.h"

SceneCorection::SceneCorection(F_lib_Fremworker::ResourceManager * _ResouseManeger)
	: SceneBase(_ResouseManeger)
{
	Text = _ResouseManeger->meshM->getText();
	scenename = L"�^�C�g��:t�L�[\n�Q�[���{�ҁFg�L�[\n�}��";

}


void SceneCorection::update()
{
	UpdateInput();

	if (GetKeyTrigger(VK_T))next = F_lib_Fremworker::Scene_title;
	else if (GetKeyTrigger(VK_G))next = F_lib_Fremworker::Scene_game;
	
}

void SceneCorection::Draw()
{
	Text->draw(scenename);

}
