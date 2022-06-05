#pragma once

#include "F_lib/include/mover.h"
#include "F_lib/include/moverManeger.h"
#include "F_lib/include/Mesh_Fbxmodel.h"
#include "Player.h"
#include "RM.h"

enum Weponid
{
	Wepon_missilelunther,
	Wepon_lyzer,
	Wepon_flamethrower,
	Wepon_showd,
	Wepon_boomerang,

	Wepon_MAX
};

struct initWepondata
{
	F_lib_Fremworker::ResourceManager* R;
	class Player* p;
	F_lib_Mover::moverList* EnemyList;
	XMFLOAT3 pos;
	float pangle;

};

//
class Wepon :public F_lib_Mover::Mover
{
public:
	Wepon(initWepondata);

	void update();
	virtual void Draw() = 0;

	void terhit(Mover*) {};
	void herhit(Mover*) {};

protected:
	virtual void move();
	virtual void ThisAtack();

	class Player* p;
	F_lib_Render::Mesh_Fbx * mesh;
	F_lib_Mover::moverList* enemylist;
	F_lib_Mover::Colision_2D* tergetcol;
	XMFLOAT3 ppos;
	XMFLOAT2 thisposold;
	bool cooltime;
	int clnokBack, cooltimeNow, cooltimeMax, countNow ,countMax;
	float atackelea,pangle,a2,nowspeed;


};

