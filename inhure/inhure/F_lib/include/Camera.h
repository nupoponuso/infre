//-------------------------------------------
//
//	DirectX11用のカメラクラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


#pragma once

//インクルード
#include "comon.h"


//定数宣言
#define ANGLEX_MAX (80)
#define ANGLEX_MIN (-80)
namespace F_lib_Render
{

	//Cameraクラス-----------------------------------------

	//　Cameraクラス
	//クラスメンバ
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

	//　Camera_3Dクラス　継承->Cameara
	//クラスメンバ
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

	//　Camera_2Dクラス　継承->Cameara
	//クラスメンバ
	class Camera_2D : public Camera
	{
	public:
		Camera_2D(int _width, int _height);

		void update() override;

	};

	//-----------------------------------------
}