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

	//D2DTextParams* d2dtext, *text2;
	//std::wstring wstr1 = L"d2dtext test line.";
	//std::wstring wstr2 = L"super long long long text line.";
	////const WCHAR* wstr = L"d2dtext test line.";
	//D2D1_RECT_F trect1 = { 0,0,300,400 };
	//D2D1_RECT_F trect2 = { 0,100,300,400 };

	//d2dtext = new D2DTextParams(wstr1, trect1);
	//text2 = new D2DTextParams(wstr1, trect2);
	//d2dtext->SetFontSize(25);
	//text2->SetFontSize(15);
	//text2->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
	//text2->SetOpacity(0.5f);
	//HRESULT hr = text2->CreateTextFormat(L"BIZ UD ゴシック", 25);
	GTimer = new GameTimer();

	TextData td1;
	td1.Str = "super long long long text line.";
	td1.Rect = { 0, 100, 200, 300 };
	td1.Data->Opacity = 1.0f;
	td1.Data->Color = D2D1::ColorF(RGB(255, 0, 0));
	td1.Data->fontSize = 80;
	//td1.Form = TextData::FORM::Point;
	td1.Data->font = Font::Impact;
	//D2DTextParams text1(&td1);
	D2DTextParams* text2 = new D2DTextParams();
	text2->SetData(&td1);
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
	UpdateInput();

	if (GetKeyTrigger(VK_G))next = F_lib_Fremworker::Scene_game;
	else if (GetKeyTrigger(VK_B))next = F_lib_Fremworker::Scene_book;

	GTimer->Update();
}

void SceneTitle::Draw()
{
	Text->draw(scenename);

}
