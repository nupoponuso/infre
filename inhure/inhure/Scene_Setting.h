#pragma once
#include "SceneManeger.h"

namespace F_lib_Render
{
#ifdef _DEBUG
	class D2DTextParams;
#endif // _DEBUG

}

class SceneSetting : public F_lib_Fremworker::SceneBase
{
public:
	SceneSetting(F_lib_Fremworker::ResourceManager* _ResourceManager);
	~SceneSetting();

	void update();
	void Draw();

private:
#ifdef _DEBUG
	F_lib_Render::D2DTextParams* Scene_Text;

#endif // _DEBUG

};