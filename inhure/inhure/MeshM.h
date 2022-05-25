#pragma once

#include "F_lib/include/MeshManeger.h"


class MeshM:public F_lib_Fremworker::MeshManeger
{
public:
	MeshM(F_lib_Render::RenderingEngine*);
	void detaLode(int);

	
};
