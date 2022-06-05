
#include "MeshM.h"
#include "F_lib/include/RenderingEngine.h"

using namespace F_lib_Render;

MeshM::MeshM(RenderingEngine * _R) :F_lib_Fremworker::MeshManeger(_R)
{
}

void MeshM::detaLode(int)
{
	Mesh_ShaderDat3D * shader;
	shader = new Mesh_ShaderDat3D(L"data/s/3Dshader.hlsl", false, Device);

	Mesh_Fbx* m;
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(),c,l);
	m->InitModel("data/m/Boss.fbx");
	m->setShader(shader);
	m->setRenderingEngine(Engine);
	fbxlist.push_back(m);

	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/tikafild.fbx");
	m->setShader(shader);
	m->setRenderingEngine(Engine); 
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(1, 0.5, 1));
	fbxlist.push_back(m);

	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/teki3.fbx");
	m->setShader(shader);
	m->setSize(0.01);
	m->setRenderingEngine(Engine);
	fbxlist.push_back(m);

	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/maru.fbx");
	m->setShader(shader);
	m->setSize(5);
	m->setRenderingEngine(Engine);
	fbxlist.push_back(m);


}
