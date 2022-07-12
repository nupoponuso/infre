#include "Scene_Collection.h"
#include "RM.h"
#include "MeshM.h"

#include "input.h"
#include "Mesh.h"
#include "RenderingEngine.h"
#include "D2DDrawMng.h"
#include "D2DText.h"

#ifdef _DEBUG
#include "Debug_Infure.h"
#endif // _DEBUG

using namespace F_lib_Render;

SceneCollection::SceneCollection(F_lib_Fremworker::ResourceManager * _ResourceManager)
	: SceneBase(_ResourceManager)
{
	Text = _ResourceManager->meshM->getText();
	scenename = L"タイトル:tキー\nゲーム本編：gキー\n図鑑";


#ifdef _DEBUG
	DebugSceneString("Collection", Scene_Text);

#endif // _DEBUG

}

SceneCollection::~SceneCollection()
{
#ifdef _DEBUG
	delete Scene_Text;
#endif // _DEBUG
	getEngine()->getD2DTextMng()->RemoveAll();
}


void SceneCollection::update()
{
	//UpdateInput();

	//if (GetKeyTrigger(VK_T))next = F_lib_Fremworker::Scene_title;
	//else if (GetKeyTrigger(VK_G))next = F_lib_Fremworker::Scene_game;
#ifdef _DEBUG
	DebugSceneChange(this);

#endif // _DEBUG

}

void SceneCollection::Draw()
{
	Text->draw(scenename);

}
