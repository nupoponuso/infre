//--------------------------
//
//		シーン用クラス　シーンの管理に使う
//
//		Scnen_Baseクラス SceneManegerクラス
//		auhor: hujioka tomoya
//
//		
//--------------------


//インクルード
#include "SceneManeger.h"
#include "ResourceManager.h"
#include "texture.h"
#include "MeshManeger.h"


namespace F_lib_Fremworker
{
	//SceneManegerクラス-----------------------------------------

	//コンストラクタ
	//PM,parameter,Sceneの初期化
	SceneManeger::SceneManeger() : Drawload(false), isload(false)
	{ }


	//デストラクタ
	//PM,parameterの削除
	SceneManeger::~SceneManeger()
	{
		delete Resource;

	}


	//updateScene関数
	//Sceneの更新と次のシーンのオーダーの取得しシーン変遷
	void SceneManeger::updateScene()
	{
		if (!Scene->getfade())
		{
			if (Scene->getnextscene() == Scene_Num)
				Scene->update();
			else
			{
				if (isload) strtSceneChange(Scene->getnextscene());
				else Drawload = true;

			}

		}
		else Scene->updetedade();

	}


	//DrawScene関数
	//Sceneの描画
	void SceneManeger::DrawScene()
	{
		if (!Drawload)
		{
			Scene->Draw();
			if (Scene->getfade() || Scene->getfadein())
				Scene->Drawfede();

		}
		else
		{
			DrawLoad();
			isload = true;

		}

	}


	//DrawLoad関数
	//ロード画面の描画
	void SceneManeger::DrawLoad()
	{
		s->reset();
		s->setPosition(0, 0);
		s->Draw();

		s->setPosition(480, -350);
		s->setSize(400, 50);
		s->setColor(1, 1, 1);
		s->Draw();

	}

	//-----------------------------------------

	//SceneBaseクラス----------------------------------------

	//コンストラクタ
	//値の初期化
	SceneBase::SceneBase(F_lib_Fremworker::ResourceManager * _ResouseManeger, bool _usefade)
		: usefade(_usefade), Resource(_ResouseManeger), s(_ResouseManeger->meshM->getSprite())
	{
		
		next = Scene_Num;
		fadealph[0] = 1.0f;
		fadealph[1] = 0;
		fadein = false;
		addfadealph = -0.01f;
		countflame = false;
		framecount = 0;

		s->reset();

	}


	//updetedade関数
	//フェードの更新
	void SceneBase::updetedade()
	{
		fadealph[0] += addfadealph;
		//Resource->meshM->getLight()->update();

		if (fadealph[(fadein) ? 1 : 0] <= fadealph[(fadein) ? 0 : 1])
		{
			usefade = false;
			s->reset();

		}

	}


	//Drawfede関数
	//フェードの描画
	void SceneBase::Drawfede()
	{
		s->reset();
		s->setColor(fadecolor);
		s->setPosition(0, 0);
		//s->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		s->setTexture(nullptr);
		s->setalph(fadealph[0]);
		s->Draw();
		s->setalph(1);
		s->setColor(1, 1, 1);

	}


	//setfadein関数
	//フェードインの設定
	void SceneBase::setfadein()
	{
		fadealph[0] = 0;
		fadealph[1] = 1.1f;
		usefade = fadein = true;
		addfadealph = 0.01f;

	}

	//-----------------------------------------
}