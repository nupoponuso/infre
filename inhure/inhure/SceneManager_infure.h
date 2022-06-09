#pragma once

#include "F_lib/include/SceneManeger.h"



class SceneManeger_inhure : public F_lib_Fremworker::SceneManeger
{
public:
	SceneManeger_inhure(F_lib_Render::RenderingEngine*);
	~SceneManeger_inhure();

	void strtSceneChange(F_lib_Fremworker::Scene_type next);

};


