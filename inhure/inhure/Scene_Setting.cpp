#include "Scene_Setting.h"

#include "RenderingEngine.h"
#include "D2DDrawMng.h"
#include "D2DText.h"

#ifdef _DEBUG
#include "Debug_Infure.h"
#endif // _DEBUG

using namespace F_lib_Render;

SceneSetting::SceneSetting(F_lib_Fremworker::ResourceManager * _ResourceManager)
	: SceneBase(_ResourceManager)
{
#ifdef _DEBUG
	DebugSceneString("Setting", Scene_Text);

#endif // _DEBUG

}

SceneSetting::~SceneSetting()
{
#ifdef _DEBUG
	delete Scene_Text;
#endif // _DEBUG
	getEngine()->getD2DTextMng()->RemoveAll();

}

void SceneSetting::update()
{
#ifdef _DEBUG
	DebugSceneChange(this);

#endif // _DEBUG

}

void SceneSetting::Draw()
{
}
