//-------------------------------------------
//
//	 DirectX11�p��light�N���X�Q | Light.cpp |
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//�C���N���[�h
#include"comon.h"
#include"Camera.h"
#include"RenderingEngine.h"

//���C�g�Ȃǂ̃R���X�^���g�o�b�t�@��`
struct CONSTANT_BUFFER_Light
{
	XMFLOAT4 LightPos;
	XMFLOAT4 eyePos;
	XMFLOAT4 LightAnbient;
};
namespace F_lib_Render
{

	//Light�N���X-----------------------------------------

	//�@Light�N���X
	//�@�N���X�����o
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

	//Light_Point�N���X-----------------------------------------

	//�@Light_Point�N���X�@�p��->Light
	//�@�N���X�����o
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