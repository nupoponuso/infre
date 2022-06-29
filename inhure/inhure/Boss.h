

#pragma once


#include "Mover2D.h"


class Boss : public Mover2D
{
public:
	Boss(F_lib_Fremworker::ResourceManager* _R);

	void update();
	void Draw();
	void terhit(Mover2D*);
	void herhit(Mover2D*);

	F_lib_Mover::Colision_2D* getcol();

protected:


};

