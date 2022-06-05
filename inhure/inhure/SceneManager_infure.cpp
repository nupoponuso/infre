#include "SceneManager_infure.h"
#include "RM.h"
#include "SceneTitle.h"
#include "Scene_Game.h"
#include "Scene_Corection.h"

using namespace F_lib_Fremworker;

SceneManeger_inhure::SceneManeger_inhure(F_lib_Render::RenderingEngine * _engine)
{
	Resource = new RM(_engine);
	Scene = new SceneTitle(Resource);
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
		Scene = new SceneCorection(Resource);
		break;

	}


}
