#pragma once

#include "Mover2D.h"
#include "MoverList.h"
#include "F_lib/include/Mesh_Fbxmodel.h"

struct initplayerdata
{
	MoverList* buletlist, *enemylist,*ebuletlist;
	F_lib_Fremworker::ResourceManager* R;

};

class Player:public Mover2D
{
public:
	Player(initplayerdata);

	void update();
	void Draw();

	void terhit(Mover2D*);
	void herhit(Mover2D*);

	F_lib_Mover::Colision_2D* getcol() override;

protected:
	void move();
	void atack();

	class Wepon* wepon[5];
	std::vector<class Equipment*> relicList;
	F_lib_Render::Mesh_Fbx* mesh;
	MoverList* myblist, *eblist, *enemylist;
	XMFLOAT3 cpos;
	bool ismove;
	int WeponNum, WeponMaxNum,rotspeed;
	float movedir, movedirold;

};

