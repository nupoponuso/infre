
#pragma once

#include "F_lib/include/ResourceManager.h"
#include "F_lib/include/RenderingEngine.h"

class RM : public F_lib_Fremworker::ResourceManager
{
public:
	RM(F_lib_Render::RenderingEngine*);

};

