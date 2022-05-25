//-------------------------------------------
//
//	DirectX11�p�̃J�����N���X 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


#pragma once

//�C���N���[�h
#include "comon.h"


//�萔�錾
#define ANGLEX_MAX (80)
#define ANGLEX_MIN (-80)
namespace F_lib_Render
{

	//Camera�N���X-----------------------------------------

	//�@Camera�N���X
	//�N���X�����o
	class Camera
	{
	public:
		Camera();
		virtual void update() = 0;

		void setPosition(XMFLOAT3 _pos) { Position = _pos; }
		void setangle(XMFLOAT3 _angle) { angle = _angle; }
		void setangleX(float _x) { angle.x = _x; }
		void setangleY(float _y) { angle.y = _y; }
		void setterget(XMFLOAT3 _pos) { Terget = _pos; }

		XMFLOAT3 GetTergetPos() { return Terget; }
		XMMATRIX GetView() { return View; }
		XMMATRIX GetProj() { return Proj; }
		XMFLOAT3 GetPos() { return Position; }
		XMFLOAT3 Getup() { return up; }
		XMFLOAT3 GetAngle() { return angle; }
		XMFLOAT4 GetProjd() { return Projpos; }

	protected:
		XMMATRIX View, Proj;
		XMFLOAT3 Position, Terget, up, angle;
		XMFLOAT4  Projpos;

	};

	//-----------------------------------------

	//Camera_3D-----------------------------------------

	//�@Camera_3D�N���X�@�p��->Cameara
	//�N���X�����o
	class Camera_3D : public Camera
	{
	public:
		Camera_3D(int _width, int _height);

		void update() override;


	private:
		float LenghthInterval;
		bool luckatterget;
	};

	//-----------------------------------------

	//�@Camera_2D�N���X�@�p��->Cameara
	//�N���X�����o
	class Camera_2D : public Camera
	{
	public:
		Camera_2D(int _width, int _height);

		void update() override;

	};

	//-----------------------------------------
}