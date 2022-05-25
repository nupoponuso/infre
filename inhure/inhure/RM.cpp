#include "RM.h"

#include "MeshM.h"
#include "TM.h"
#include "F_lib/include/EffekseerManeger.h"
#include "F_lib/include/RenderingEngine.h"


RM::RM(F_lib_Render::RenderingEngine * _engine) :F_lib_Fremworker::ResourceManager()
{
	meshM = new MeshM(_engine);
	TM = new TexM(_engine->getDevice());

	Em = new F_lib_Render::EffekseerManeger(_engine->getDevice(), _engine->getDeviceContext(), (F_lib_Render::Camera_3D*)meshM->getCamera());
	_engine->setEfect(Em);
}
