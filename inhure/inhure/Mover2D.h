#pragma once
#include "F_lib/include/mover.h"

enum moverId
{
	mover_player,
	mover_enemy,
	mover_bullet,
	mover_item,
	mover_obstacle,

	mover_max
};

class Mover2D:public F_lib_Mover::MoverBase
{
public:
	Mover2D(F_lib_Fremworker::ResourceManager* _R) :F_lib_Mover::MoverBase(_R) {}

	virtual void update() = 0;
	virtual void Draw() = 0;
	virtual void terhit(Mover2D*) = 0;
	virtual void herhit(Mover2D*) = 0;

	virtual F_lib_Mover::Colision_2D* getcol() = 0;
	moverId getMyid() { return Myid; }

protected:
	F_lib_Mover::Colision_2D* col;
	moverId Myid;
	float speed;
	int atack;

};

