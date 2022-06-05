#pragma once

#include "F_lib/include/mover.h"
#include "F_lib/include/moverManeger.h"
#include "F_lib/include/Mesh_Fbxmodel.h"

struct initplayerdata
{
	F_lib_Mover::moverList* buletlist, *enemylist,*ebuletlist;
	F_lib_Fremworker::ResourceManager* R;

};

class Player:public F_lib_Mover::Mover
{
public:
	Player(initplayerdata);

	void update();
	void Draw();

	void terhit(F_lib_Mover::Mover*);
	void herhit(F_lib_Mover::Mover*);

	F_lib_Mover::Colision_2D* getcol() override;

protected:
	void move();
	void atack();

	class Wepon* wepon[5];

	F_lib_Render::Mesh_Fbx* mesh;
	F_lib_Mover::moverList* myblist, *eblist, *enemylist;
	XMFLOAT3 cpos;
	bool ismove;
	int WeponNum, WeponMaxNum,rotspeed;
	float movedir, movedirold;
};

