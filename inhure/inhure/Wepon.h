#pragma once

#include "Mover2D.h"
#include "MoverList.h"
#include "F_lib/include/Mesh_Fbxmodel.h"
#include "Player.h"
#include "RM.h"

enum weponId
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
	MoverList* EnemyList;
	XMFLOAT3 pos;
	float pangle;

};

//
class Wepon :public Mover2D
{
public:
	Wepon(initWepondata);

	void update();
	virtual void Draw() = 0;

	void terhit(Mover2D*) {};
	void herhit(Mover2D*) {};

	F_lib_Mover::Colision_2D* getcol() { return nullptr; }

protected:
	virtual void move();
	virtual void ThisAtack();

	class Player* p;
	F_lib_Render::Mesh_Fbx * mesh;
	MoverList* enemylist;
	F_lib_Mover::Colision_2D* tergetcol;
	XMFLOAT3 ppos;
	XMFLOAT2 thisposold;

	bool cooltime;
	int cooltimeNow, cooltimeMax, countNow ,countMax;
	float atackelea,pangle,a2,nowspeed;
	int atack, lockOn, nockBack;
	float atackLen;

};

