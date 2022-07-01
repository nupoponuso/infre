#pragma once
#include "F_lib/include/SceneManeger.h"
#include "F_lib/include/Text.h"


class SceneCorection :public F_lib_Fremworker::SceneBase
{
public:
	SceneCorection(F_lib_Fremworker::ResourceManager* _ResouseManeger);

	void update();
	void Draw();

private:
	F_lib_Render::Text* Text;
	std::wstring scenename;

	class Mover2D* models[37];
};

