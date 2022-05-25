#pragma once

#include "F_lib/include/SceneManeger.h"
#include "F_lib/include/Text.h"

class SceneGame :public F_lib_Fremworker::SceneBase
{
public:
	SceneGame(F_lib_Fremworker::ResourceManager* _ResouseManeger);

	void update();
	void Draw();

private:
	F_lib_Render::Text* Text;
	std::wstring scenename;

};

