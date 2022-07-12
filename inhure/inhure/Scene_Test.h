#pragma once
#include "SceneManeger.h"


//‘O•ûéŒ¾
namespace F_lib_Render
{
	class D2DTextParams;
	class D2DCircleGauge;
}
class GameTimer;
class Mover2D;
class MoverList;
namespace F_lib_Mover
{
}


class SceneTest : public F_lib_Fremworker::SceneBase
{
public:
	SceneTest(F_lib_Fremworker::ResourceManager* _ResourceManager);
	~SceneTest();

	void update();
	void Draw();

private:
	F_lib_Render::D2DTextParams* Scene_Text;
	GameTimer* GTimer;
	F_lib_Render::D2DCircleGauge* Gauge;

	Mover2D* models[37];
	Mover2D* mmm;

	MoverList* elist, *eblist, *blist, *Itemlist;
	Mover2D* p;

};


