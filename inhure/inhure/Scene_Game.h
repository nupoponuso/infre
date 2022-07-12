#pragma once

#include "F_lib/include/SceneManeger.h"
#include "F_lib/include/Text.h"
#include "MoverList.h"
#include "Player.h"
#include "EnemySpawner.h"

namespace F_lib_Render
{
#ifdef _DEBUG
	class D2DTextParams;
#endif // _DEBUG

}

class SceneGame :public F_lib_Fremworker::SceneBase
{
public:
	SceneGame(F_lib_Fremworker::ResourceManager* _ResouseManeger);
	~SceneGame();

	void update();
	void Draw();

private:
	class UI* pui;
	F_lib_Render::Text* Text;
	std::wstring scenename,hit;
	Mover2D* p;
	MoverList* elist, *eblist,* blist,*Itemlist;
	F_lib_Render::Mesh_Fbx* fild;
	F_lib_Render::Mesh_billbord* b;
	class EnemySpawner* spawner;
	class GameArea* area[4];

#ifdef _DEBUG
	F_lib_Render::D2DTextParams* Scene_Text;

#endif // _DEBUG

};

