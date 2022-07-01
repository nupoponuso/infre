
#include "MeshM.h"
#include "F_lib/include/RenderingEngine.h"

using namespace F_lib_Render;

MeshM::MeshM(RenderingEngine * _R) :F_lib_Fremworker::MeshManeger(_R)
{
}

void MeshM::detaLode(int)
{

	Mesh_Fbx* m;
	//0
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(),c,l);
	m->InitModel("data/m/Boss.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	fbxlist.push_back(m);

	//1
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/tikafild.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine); 
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(1, 0.5, 1));
	fbxlist.push_back(m);

	//2
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/teki3.fbx");
	m->setShader(shder3D);
	m->setSize(0.01f);
	m->setRenderingEngine(Engine);
	fbxlist.push_back(m);

	//3
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/maru.fbx");
	m->setShader(shder3D);
	m->setSize(5);
	m->setRenderingEngine(Engine);
	fbxlist.push_back(m);
	
	//boss
	//4
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/boss/coreunit_01.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//5
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/boss/coreunit_01_fist.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//6
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/boss/coreunit_01_fist_incolor.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//7
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/boss/coreunit_01_incolor_01.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//8
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/boss/coreunit_01_incolor_02.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//9
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/boss/timeboss.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//enemy
	//10
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_01.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//11
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_01_incolor_01.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//12
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_01_incolor_02.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//13
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_01_incolor_03.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//14
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_02.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//15
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_02_incolor_01.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//16
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_02_incolor_02.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//17
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_02_incolor_03.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//18
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_03.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//19
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_03_incolor_01.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//20
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_03_incolor_02.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//21
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_03_incolor_03.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//22
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_04.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//23
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_04_incolor_01.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//24
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_04_incolor_02.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//25
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_04_incolor_03.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//26
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_05.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//27
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_05_incolor_01.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//28
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_05_incolor_02.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//29
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/enemy/battleship_05_incolor_03.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//player
	//30
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/player/playership_01.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//31
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/player/playership_01_incolor_01.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//32
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/player/playership_01_incolor_02.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);
	
	//33
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/player/playership_01_incolor_03.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//34
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/player/playership_01_incolor_04.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//35
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/player/playership_01_incolor_05.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.1f, 0.1f, 0.1f));
	fbxlist.push_back(m);

	//36
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/player/playership_01_incolor_06.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(0.01f, 0.01f, 0.01f));
	fbxlist.push_back(m);

	//37
	m = new Mesh_Fbx(Engine->getDevice(), Engine->getDeviceContext(), c, l);
	m->InitModel("data/m/boss/untitled.fbx");
	m->setShader(shder3D);
	m->setRenderingEngine(Engine);
	m->setPosition(XMFLOAT3(0, -20, 0));
	m->setSize(XMFLOAT3(1.0f, 1.0f, 1.0f));
	fbxlist.push_back(m);

}
