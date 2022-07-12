#include "Scene_Test.h"

#include <sstream>

#include "input.h"
#include "Mesh.h"
#include "MeshM.h"
#include "DisplayMover.h"
#include "RenderingEngine.h"
#include "D2DDrawMng.h"
#include "D2DText.h"
#include "GameTimer.h"
#include "D2DFunctions.h"
#include "DisplayMover.h"
#include "Player.h"
#include "Debug_Infure.h"
#include "MoverList.h"

using namespace F_lib_Render;

SceneTest::SceneTest(F_lib_Fremworker::ResourceManager * _ResourceManager)
	: SceneBase(_ResourceManager)
{
#pragma region Camera
	//XMFLOAT3 s_pos = { 1280 / 2 + 100,800 / 2 - 100, 0 };
	//_ResourceManager->meshM->getCamera()->setPosition({ 0,150,0 });
	_ResourceManager->meshM->getCamera()->setangle(XMFLOAT3(-89.99f, 0, 0));
	//_ResourceManager->meshM->getCamera()->update();
#pragma endregion


#pragma region CharacterTest
	XMFLOAT3 s_pos = { 0,0,0 };
	initdisplaydata datd[37];
	for (int i = 0; i < 37; i++) {
		datd[i].R = _ResourceManager;
		//datd[i].pos = { s_pos.x + 1000 * i % 10, 0, s_pos.y + 1000 * i % 10 };
		datd[i].pos = s_pos;
		datd[i].size = 1.0f;
		datd[i].modelId = i;
		models[i] = new DisplayMover(datd[i]);
	}
	
	float i = 0;
	for (auto&& m : models) {
		if (!m) {
			continue;
		} else {
			DisplayMover* mm = dynamic_cast<DisplayMover*>(m);
			mm->SetPos({ i, 0, 0 });
		}
		i += 10;
	}

	//initdisplaydata dat;
	//dat.R = _ResourceManager;
	//dat.pos = { 0,0,0 };
	//dat.size = 0.1f;
	//dat.modelId = 36;
	//mmm = new DisplayMover(dat);
#pragma endregion

#pragma region Player
	elist = new MoverList();
	eblist = new MoverList();
	blist = new MoverList();
	Itemlist = new MoverList();

	initplayerdata datp;
	datp.R = _ResourceManager;
	datp.enemyList = elist;
	datp.bulletList = blist;
	datp.enemybList = eblist;
	datp.itemList = Itemlist;

	p = new Player(datp);
#pragma endregion


#pragma region D2DTextDisplayTest
	TextData td1;
	td1.Str = "super long long long text line.";
	td1.Pos = { -1280/2,-800 / 2 +100 };
	td1.Rect = { 600, -400, 900, 300 };
	td1.Data->Opacity = 1.0f;
	td1.Data->Color = D2D1::ColorF(D2D1::ColorF::White);
	td1.Data->fontSize = 80;
	//td1.Form = TextData::FORM::Rect;
	td1.Data->font = Font::Impact;

	D2DTextParams* text1 = new D2DTextParams();
	text1->SetData(&td1);

	TextData td2 = td1;
	td2.Rect = { 0, 100, 900, -300 };
	td2.Form = TextData::FORM::Rect;
	td2.Data = new FontData();
	td2.Data->fontSize = 50;
	td2.Data->Color = D2D1::ColorF(D2D1::ColorF::Red);
	D2DTextParams* text2 = new D2DTextParams(&td2);
	
	TextData td3 = td1;
	td3.Data = new FontData();
	td3.Data->Color = D2D1::ColorF(D2D1::ColorF::Blue);
	D2DTextParams* text3 = new D2DTextParams("Long Long Long TEXT\n",
		{ -200,100 }, { -200,100,100,-100 },
		TextData::FORM::Rect, td3.Data);
#pragma endregion


#pragma region GameTimerTest
	GTimer = new GameTimer();
#pragma endregion


#pragma region D2DFuncTest
	Gauge = new D2DCircleGauge();
	Gauge->Create({ 500, 500 }, 50, 20);
#pragma endregion


	// デバッグ表示関係
	DisplayFontList({ -1280 / 2,800 / 2 });
	DebugSceneString("Test", Scene_Text);
}

SceneTest::~SceneTest()
{
	delete GTimer;
	delete Gauge;
	delete Scene_Text;
	delete p;
	delete mmm;
	for (auto&& m : models) {
		delete m;
	}

	getEngine()->getD2DTextMng()->RemoveAll();
}

void SceneTest::update()
{

	DebugSceneChange(this);
	
#pragma region D2DTextOriginTest
	// D2DTextの原点位置変更テスト
	static int inp = 0;
	if (GetKeyTrigger(VK_SPACE)) {
		inp++;
		if (inp >= 5) {
			inp = 0;
		}
		getEngine()->getD2DText()->SetOrigin(static_cast<D2DText::ORIGIN>(inp));
	}
	if (GetKeyTrigger(VK_Y)) {
		getEngine()->getD2DText()->ReverseYAxis(true);
	}
	else if (GetKeyTrigger(VK_U)) {
		getEngine()->getD2DText()->ReverseYAxis(false);
	}
#pragma endregion


#pragma region Display
	for (auto&& m: models) {
		m->Update();
	}

	static int num = 0;
	if (GetKeyTrigger(VK_RIGHT)) {
		if (num <= 0) {
			num = 0;
		}
		if (!models[num]) {

		} else {
			DisplayMover* mm = dynamic_cast<DisplayMover*>(models[num]);
			mm->SetEdit(false);
		}

		num++;

		if (!models[num]) {
			
		} else {
			DisplayMover* mm = dynamic_cast<DisplayMover*>(models[num]);
			mm->SetEdit(true);
		}
		
	}

#pragma endregion

	GTimer->Update();
	//for (auto&& m : models) {
	//	m->Update();
	//}


	//mmm->Update();
#pragma region Player
	p->Update();
#pragma endregion
}

void SceneTest::Draw()
{
	//描画は4番目から
	for (int i = 4; i < 37; i++) {
		models[i]->Draw();
	}

	//for (auto&& m : models) {
	//	m->Draw();
	//}

	//mmm->Draw();
#pragma region Player
	p->Draw();
#pragma endregion
}
