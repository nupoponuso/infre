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

	TextData td1;
	td1.Str = "super long long long text line.";
	td1.Rect = { 600, 100, 900, 300 };
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

	DisplayFontList();

	Gauge = new D2DCircleGauge();
	Gauge->Create({ 500, 500 }, 50, 20);
}

SceneTitle::~SceneTitle()
{
	delete GTimer;
	delete Gauge;
	getEngine()->getD2DTextMng()->RemoveAll();
}

void SceneTitle::update()
{
	if (GetKeyTrigger(VK_G))next = F_lib_Fremworker::Scene_game;
	else if (GetKeyTrigger(VK_B))next = F_lib_Fremworker::Scene_book;

	if (CustomInput::getins()->GetCustomInputTrigger(GameInput::OK))
		int i = 0;

	GTimer->Update();
}

void SceneTitle::Draw()
{
	s->setPosition(XMFLOAT2());
	s->setSize(50);
	s->setTexture(Resource->TM->gettex(0));
	s->RDraw(true);

	Text->setalpa(0.5);
	Text->draw(scenename);

}
