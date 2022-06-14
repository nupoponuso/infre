#pragma once

#include "Mover2D.h"
#include "MoverList.h"
#include "F_lib/include/Mesh_Fbxmodel.h"


struct initenemydata
{
	F_lib_Fremworker::ResourceManager * R;
	MoverList* bulletlist,*mylist;
	class Player* p;
	XMFLOAT3 pos;
	float speed;

};

class Enemy:public Mover2D
{
public:
	Enemy(initenemydata);
	
	void update();
	void Draw();
	void terhit(Mover2D*);
	void herhit(Mover2D*);

	F_lib_Mover::Colision_2D* getcol();

	class Player* getPlayer() { return p; }

protected:
	virtual void move() = 0;

	class Player* p;
	F_lib_Render::Mesh_Fbx* mesh;
	MoverList* bulletList,*myList;
	int hp, atack, defense;
	float speed;

};

