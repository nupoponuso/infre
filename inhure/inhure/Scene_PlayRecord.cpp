#include "Scene_PlayRecord.h"

#include "RenderingEngine.h"
#include "D2DDrawMng.h"
#include "D2DText.h"


#ifdef _DEBUG
#include "Debug_Infure.h"
#endif // _DEBUG
using namespace F_lib_Render;

ScenePlayRecord::ScenePlayRecord(F_lib_Fremworker::ResourceManager * _ResourceManager)
	: SceneBase(_ResourceManager)
{
#ifdef _DEBUG
	DebugSceneString("PlayRecord", Scene_Text);

#endif // _DEBUG

}

ScenePlayRecord::~ScenePlayRecord()
{
#ifdef _DEBUG
	delete Scene_Text;
#endif // _DEBUG
	getEngine()->getD2DTextMng()->RemoveAll();

}

void ScenePlayRecord::update()
{
#ifdef _DEBUG
	DebugSceneChange(this);

#endif // _DEBUG

}

void ScenePlayRecord::Draw()
{
}
