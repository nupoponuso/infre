#include "Scene_Corection.h"
#include "RM.h"
#include "MeshM.h"

#include "input.h"

#include "DisplayMover.h"

SceneCorection::SceneCorection(F_lib_Fremworker::ResourceManager * _ResouseManeger)
	: SceneBase(_ResouseManeger)
{
	Text = _ResouseManeger->meshM->getText();
	scenename = L"タイトル:tキー\nゲーム本編：gキー\n図鑑";

	XMFLOAT3 s_pos = { 1280 / 2 + 100,800 / 2 - 100, 0 };

	initdisplaydata datd[37];
	for (int i = 0; i < 37; i++) {
		datd[i].R = _ResouseManeger;
		datd[i].pos = { s_pos.x + 1000 * i % 10, s_pos.y + 1000 * i % 10, 0 };
		datd[i].modelId = i;
		models[i] = new DisplayMover(datd[i]);
	}




}


void SceneCorection::update()
{
	UpdateInput();

	if (GetKeyTrigger(VK_T))next = F_lib_Fremworker::Scene_title;
	else if (GetKeyTrigger(VK_G))next = F_lib_Fremworker::Scene_game;
	
	for (auto&& m : models) {
		m->Update();
	}
}

void SceneCorection::Draw()
{
	Text->draw(scenename);

	for (auto&& m : models) {
		m->Draw();
	}
}
