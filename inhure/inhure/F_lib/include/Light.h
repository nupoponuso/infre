//-------------------------------------------
//
//	 DirectX11用のlightクラス群 | Light.cpp |
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//インクルード
#include"comon.h"
#include"Camera.h"
#include"RenderingEngine.h"

//ライトなどのコンスタントバッファ定義
struct CONSTANT_BUFFER_Light
{
	XMFLOAT4 LightPos;
	XMFLOAT4 eyePos;
	XMFLOAT4 LightAnbient;
};
namespace F_lib_Render
{

	//Lightクラス-----------------------------------------

	//　Lightクラス
	//　クラスメンバ
	class Light
	{
	public:
		Light();
		void setLightPos(XMFLOAT3 _Pos) { LightPos = _Pos; }

		XMFLOAT4 GetLightDir() { return LightDir; }
		XMFLOAT3 GetLightPos() { return LightPos; }
		void setLightDir(XMFLOAT4 _Dir) { LightDir = _Dir; }

	protected:
		XMFLOAT3 LightPos;
		XMFLOAT4 LightDir;
		XMFLOAT4 Anbient;

	};

	//-----------------------------------------

	//Light_Pointクラス-----------------------------------------

	//　Light_Pointクラス　継承->Light
	//　クラスメンバ
	class Light_Point :public Light
	{
	public:
		Light_Point(Camera_3D*);
		~Light_Point();

		void init(F_lib_Render::RenderingEngine*);

		void update();
		XMMATRIX getLight() { return World; }
		XMMATRIX getShadowUV() { return UV; }

	private:
		ID3D11DeviceContext* DeviceContext;
		ID3D11Buffer* ConstantBufferL;
		Camera_3D* c;
		XMMATRIX World, UV;

	};

	//-----------------------------------------
}