//-------------------------------------------
//
//		meshmanegerクラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//インクルード
#include "MeshManeger.h"
#include "RenderingEngine.h"
#include "Light.h"


namespace F_lib_Fremworker
{
	using namespace F_lib_Render;
	//コンストラクタ
	//初期化
	MeshManeger::MeshManeger(RenderingEngine* _engine) : dateManeger(_engine->getDevice(), _engine->getDeviceContext()),Engine(_engine)
	{
		
		c = new Camera_3D((int)_engine->getWindowsize().x, (int)_engine->getWindowsize().y);
		l = new Light_Point((Camera_3D*)c);
		l->init(_engine);
		Sprite = new Mesh_Sprite(Device, DeviceContext, new Camera_2D(_engine->getWindowsize().x, _engine->getWindowsize().y));
		Sprite->InitModel();
		Mesh_ShaderDat* Shader = new Mesh_ShaderDat2D(L"data/s/2Dshader.hlsl",Device);
		Sprite->setShader(Shader);
		Sprite->setSize(XMFLOAT2(100, 100));
		Sprite->setRenderingEngine(_engine);
		Billbord = new Mesh_billbord(Device, DeviceContext, (Camera_3D*)c);
		Billbord->InitModel();
		Billbord->setShader(Shader);
		Billbord->setRenderingEngine(_engine);

		_engine->setSprite(Sprite);
		_engine->setBillBord(Billbord);
		text = _engine->getText();

	}

}