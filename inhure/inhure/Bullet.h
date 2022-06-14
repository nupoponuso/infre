#pragma once

#include "Mover2D.h"
#include "MoverList.h"
#include "F_lib/include/Mesh_Fbxmodel.h"

struct initbulletdata
{
	F_lib_Fremworker::ResourceManager* R;
	MoverList* atacklist;
	XMFLOAT3 pos;
	float speed, angle,size;
	int atack;

}; 


class Bullet :public Mover2D
{
public:
	Bullet(initbulletdata);
	void update();
	void Draw();

	void terhit(Mover2D*);
	void herhit(Mover2D*) {}

	F_lib_Mover::Colision_2D* getcol() override;

protected:
	virtual void move();
	virtual void myhit();

	F_lib_Render::Mesh_Fbx* mesh;
	MoverList* atacklist;
	
	//XMFLOAT2 vel;
	int count;


};

