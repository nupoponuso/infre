#include "SceneManager_infure.h"
#include "RM.h"
#include "SceneTitle.h"
#include "Scene_Game.h"
#include "Scene_Collection.h"
#include "Scene_Achivement.h"
#include "Scene_PlayRecord.h"
#include "Scene_Setting.h"
#include "Scene_Test.h"


using namespace F_lib_Fremworker;

SceneManeger_inhure::SceneManeger_inhure(F_lib_Render::RenderingEngine * _engine)
{
	Resource = new RM(_engine);
#ifdef _DEBUG
	Scene = new SceneTest(Resource);
#else
	Scene = new SceneTitle(Resource);
#endif // _DEBUG
	isload = true;

}

SceneManeger_inhure::~SceneManeger_inhure()
{
}

void SceneManeger_inhure::strtSceneChange(Scene_type next)
{
	delete Scene;

	switch (next)
	{
	case Scene_type::Scene_title:
		Scene = new SceneTitle(Resource);
		break;
	case Scene_type::Scene_game:
		Scene = new SceneGame(Resource);
		break;
	case Scene_type::Scene_book:
		Scene = new SceneCollection(Resource);
		break;
	case Scene_type::Scene_achievement:
		Scene = new SceneAchivement(Resource);
		break;
	case Scene_type::Scene_record:
		Scene = new ScenePlayRecord(Resource);
		break;
	case Scene_type::Scene_setting:
		Scene = new SceneSetting(Resource);
		break;
	case Scene_type::Scene_test:
		Scene = new SceneTest(Resource);
		break;
	default:
		break;
	}


}
