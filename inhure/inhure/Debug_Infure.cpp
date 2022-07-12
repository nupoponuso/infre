#include "Debug_Infure.h"

#include <sstream>

#include "input.h"
#include "SceneManeger.h"
#include "D2DText.h"

//=============================================================================
//	デバッグ用関数
//=============================================================================
void DebugSceneChange(F_lib_Fremworker::SceneBase * scene)
{
	//UpdateInput();

	using ST = F_lib_Fremworker::Scene_type;

	if (GetKeyTrigger(VK_F1)) {
		scene->setNextScene(ST::Scene_title);
	} else if (GetKeyTrigger(VK_F2)) {
		scene->setNextScene(ST::Scene_game);
	} else if (GetKeyTrigger(VK_F3)) {
		scene->setNextScene(ST::Scene_book);
	} else if (GetKeyTrigger(VK_F4)) {
		scene->setNextScene(ST::Scene_achievement);
	} else if (GetKeyTrigger(VK_F5)) {
		scene->setNextScene(ST::Scene_record);
	} else if (GetKeyTrigger(VK_F6)) {
		scene->setNextScene(ST::Scene_setting);
	} else if (GetKeyTrigger(VK_F9) && GetKeyPress(VK_D)) {
		scene->setNextScene(ST::Scene_test);
	}
}

void DebugSceneString(std::string str, F_lib_Render::D2DTextParams * text)
{
	using namespace F_lib_Render;

	TextData td;
	std::stringstream ss;
	ss << "Scene : " << str;
	td.Str = ss.str();
	td.Pos = { 1280 / 2 - 200, 800 / 2 };
	td.Data->Color = D2D1::ColorF(D2D1::ColorF::White);
	td.Data->fontSize = 20;
	td.Form = TextData::FORM::Point;
	text = new D2DTextParams();
	text->SetData(&td);

}
