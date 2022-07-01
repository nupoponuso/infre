#include "SceneTitle.h"
#include "RM.h"
#include "MeshM.h"

#include "CustomInput.h"
#include "input.h"

#include "RenderingEngine.h"
#include "D2DDrawMng.h"
#include "D2DText.h"
using namespace F_lib_Render;

SceneTitle::SceneTitle(F_lib_Fremworker::ResourceManager * _R)
	: SceneBase(_R)
{
	Resource->TM->loadTex();
	Text = _R->meshM->getText();
	scenename = L"タイトル\nゲーム本編：gキー\n図鑑：bキー";


	GTimer = new GameTimer();
	getEngine()->getD2DText()->SetOrigin(D2DText::ORIGIN::LEFTTOP);
	getEngine()->getD2DText()->ReverseYAxis(false);

	//std::string str1 = "str test line.";
	//D2D1_RECT_F strrect1 = { 300, 0,  600, 200 };
	//d2dtext->DrawString(str1, strrect1);

}

SceneTitle::~SceneTitle()
{
	delete GTimer;
	getEngine()->getD2DTextMng()->RemoveAll();
}

void SceneTitle::update()
{
	if (GetKeyTrigger(VK_G))next = F_lib_Fremworker::Scene_game;
	else if (GetKeyTrigger(VK_B))next = F_lib_Fremworker::Scene_book;

	if (CustomInput::getins()->getTrigger(GameInput::OK))
		int i = 0;

	GTimer->Update();
}

void SceneTitle::Draw()
{


	Text->setalpa(0.5);
	Text->draw(scenename);

}
