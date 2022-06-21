#pragma once

#include "F_lib/include/SceneManeger.h"
#include "F_lib/include/Text.h"
#include "GameTimer.h"

class SceneTitle : public F_lib_Fremworker::SceneBase
{
public:
	SceneTitle(F_lib_Fremworker::ResourceManager* _R);
	~SceneTitle();

	void update();
	void Draw();

private:
	F_lib_Render::Text* Text;
	std::wstring scenename;
	GameTimer* GTimer;
};

