#include "Scene_Achivement.h"

#include "RenderingEngine.h"
#include "D2DDrawMng.h"
#include "D2DText.h"


#ifdef _DEBUG
#include "Debug_Infure.h"
#endif // _DEBUG
using namespace F_lib_Render;

SceneAchivement::SceneAchivement(F_lib_Fremworker::ResourceManager * _ResourceManager)
	: SceneBase(_ResourceManager)
{
#ifdef _DEBUG
	DebugSceneString("Achievement", Scene_Text);

#endif // _DEBUG

}

SceneAchivement::~SceneAchivement()
{
#ifdef _DEBUG
	delete Scene_Text;
#endif // _DEBUG
	getEngine()->getD2DTextMng()->RemoveAll();

}

void SceneAchivement::update()
{
#ifdef _DEBUG
	DebugSceneChange(this);

#endif // _DEBUG

}

void SceneAchivement::Draw()
{
}
