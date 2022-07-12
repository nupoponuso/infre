#pragma once

#include "F_lib/include/SceneManeger.h"
#include "F_lib/include/Text.h"

namespace F_lib_Render
{
#ifdef _DEBUG
	class D2DTextParams;
#endif // _DEBUG

}

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

#ifdef _DEBUG
	F_lib_Render::D2DTextParams* Scene_Text;

#endif // _DEBUG
};

