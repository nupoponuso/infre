#pragma once

#include "F_lib/include/mover.h"
#include "F_lib/include/moverManeger.h"
#include "F_lib/include/Mesh_Fbxmodel.h"


struct initenemydata
{
	F_lib_Fremworker::ResourceManager * R;
	F_lib_Mover::moverList* bulletlist;
	class Player* p;
	XMFLOAT3 pos;
	float speed;

};

class Enemy:public F_lib_Mover::Mover
{
public:
	Enemy(initenemydata);
	
	void update();
	void Draw();
	void terhit(Mover*);
	void herhit(Mover*);

	F_lib_Mover::Colision_2D* getcol();

protected:
	virtual void move() = 0;

	class Player* p;
	F_lib_Render::Mesh_Fbx* mesh;
	F_lib_Mover::moverList* bulletlist;

};

