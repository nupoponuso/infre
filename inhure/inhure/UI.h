#pragma once

#include "F_lib/include/ResourceManager.h"
#include "F_lib/include/Mesh_Sprite.h"


//　UIクラス
//　ゲーム内のUIの基底クラス
class UI
{
public:
	UI(F_lib_Fremworker::ResourceManager* _R);

	virtual void Update() = 0;
	virtual void Draw() = 0;

private:
	F_lib_Fremworker::ResourceManager* R;	//リソース
	F_lib_Render::Mesh_Sprite* s;			//スプライト

};

