#pragma once

#include "F_lib/include/SceneManeger.h"
#include "F_lib/include/Text.h"
#include "F_lib/include/moverManeger.h"
#include "Player.h"
#include "EnemySpawner.h"

class SceneGame :public F_lib_Fremworker::SceneBase
{
public:
	SceneGame(F_lib_Fremworker::ResourceManager* _ResouseManeger);

	void update();
	void Draw();

private:
	F_lib_Render::Text* Text;
	std::wstring scenename,hit;
	F_lib_Mover::Mover* p;
	F_lib_Mover::moverList* elist, *eblist,* blist;
	F_lib_Render::Mesh_Fbx* fild;
	EnemySpawner* spawner;

};

