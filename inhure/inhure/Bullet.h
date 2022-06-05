#pragma once

#include "F_lib/include/mover.h"
#include "F_lib/include/moverManeger.h"
#include "F_lib/include/Mesh_Fbxmodel.h"

struct initbulletdata
{
	F_lib_Fremworker::ResourceManager* R;
	F_lib_Mover::moverList* atacklist;
	XMFLOAT3 pos;
	float speed, angle,size;

}; 


class Bullet :public F_lib_Mover::Mover
{
public:
	Bullet(initbulletdata);
	void update();
	void Draw();

	void terhit(Mover*);
	void herhit(Mover*) {}

	F_lib_Mover::Colision_2D* getcol() override;

protected:
	void move();
	void myhit();

	F_lib_Render::Mesh_Fbx* mesh;
	F_lib_Mover::moverList* atacklist;
	
	//XMFLOAT2 vel;
	int count;


};

