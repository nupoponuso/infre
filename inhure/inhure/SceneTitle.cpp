#include "SceneTitle.h"
#include "RM.h"
#include "MeshM.h"

#include "input.h"

#include "RenderingEngine.h"
#include "D2DDrawMng.h"
#include "D2DText.h"
using namespace F_lib_Render;

SceneTitle::SceneTitle(F_lib_Fremworker::ResourceManager * _R)
	: SceneBase(_R)
{
	Text = _R->meshM->getText();
	scenename = L"タイトル\nゲーム本編：gキー\n図鑑：bキー";

	D2DText* d2dtext;
	//std::wstring wstr = L"d2dtext test line.";
	const WCHAR* wstr = L"d2dtext test line.";
	D2D1_RECT_F trect = { 0,0,300,400 };

	d2dtext = new D2DText(wstr, trect);

	GTimer = new GameTimer();
}

SceneTitle::~SceneTitle()
{
	delete GTimer;
	getEngine()->getD2DTextMng()->RemoveAll();
}

void SceneTitle::update()
{
	UpdateInput();

	if (GetKeyTrigger(VK_G))next = F_lib_Fremworker::Scene_game;
	else if (GetKeyTrigger(VK_B))next = F_lib_Fremworker::Scene_book;

	GTimer->Update();
}

void SceneTitle::Draw()
{
	Text->draw(scenename);

}
