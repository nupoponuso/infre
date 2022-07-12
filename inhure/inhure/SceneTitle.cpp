#include "SceneTitle.h"
#include "RM.h"
#include "MeshM.h"

#include "input.h"

#ifdef _DEBUG
#include "Debug_Infure.h"
#endif // _DEBUG

#include "RenderingEngine.h"
#include "D2DDrawMng.h"
#include "D2DText.h"
using namespace F_lib_Render;

SceneTitle::SceneTitle(F_lib_Fremworker::ResourceManager * _R)
	: SceneBase(_R)
{
	Text = _R->meshM->getText();
	scenename = L"タイトル\nゲーム本編：gキー\n図鑑：bキー";



#ifdef _DEBUG
	DebugSceneString("Title", Scene_Text);

#endif // _DEBUG


}

SceneTitle::~SceneTitle()
{
#ifdef _DEBUG
	delete Scene_Text;
#endif // _DEBUG
	getEngine()->getD2DTextMng()->RemoveAll();
}

void SceneTitle::update()
{
	UpdateInput();

	//if (GetKeyTrigger(VK_G))next = F_lib_Fremworker::Scene_game;
	//else if (GetKeyTrigger(VK_B))next = F_lib_Fremworker::Scene_book;
#ifdef _DEBUG
	DebugSceneChange(this);

#endif // _DEBUG

}

void SceneTitle::Draw()
{
	Text->draw(scenename);

}
