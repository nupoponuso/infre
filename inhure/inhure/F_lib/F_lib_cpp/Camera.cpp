//-------------------------------------------
//
//	DirectX11用のカメラクラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//インクルード
#include "Camera.h"

//定数宣言
#define NEAR_Z (1.0f)
#define FER_Z  (30000.0f)

namespace F_lib_Render
{
	//Camera＿３Dクラス-----------------------------------------

	//コンストラクタ
	//値の初期化
	Camera::Camera()
	{
		up = XMFLOAT3(0, 1, 0);

		angle = XMFLOAT3(0, 0, 0);
		View = Proj = XMMatrixIdentity();

	}


	//Cameara３Dクラスのコンストラクタ
	//3Dカメラ用の値の初期化
	Camera_3D::Camera_3D(int _width, int _height)
	{
		Position = XMFLOAT3(0.0, 0, 100);
		Terget = XMFLOAT3(0.0, 0.0, 0.0);

		Projpos = XMFLOAT4(45.0f, ((float)_width / (float)_height), NEAR_Z, FER_Z);

		LenghthInterval = sqrtf((Position.x - Terget.x)*(Position.x - Terget.x) + (Position.z - Terget.z)*(Position.z - Terget.z));
	}


	//update関数
	//毎フレームごとの更新
	void Camera_3D::update()
	{
		if (angle.x > ANGLEX_MAX) angle.x = ANGLEX_MAX;
		if (angle.x < ANGLEX_MIN) angle.x = ANGLEX_MIN;

		Terget.x = Position.x + sindeg(angle.y) * cosdeg(angle.x) * LenghthInterval;
		Terget.z = Position.z + cosdeg(angle.y) * cosdeg(angle.x) * LenghthInterval;
		Terget.y = Position.y + sindeg(angle.x) * LenghthInterval;

		View = XMMatrixLookAtLH(XMLoadFloat3(&Position), XMLoadFloat3(&Terget), XMLoadFloat3(&up));
		Proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(Projpos.x), Projpos.y, Projpos.z, Projpos.w);

	}


	//-----------------------------------------------------------

	//Camera_2Dクラス-----------------------------------------

	//コンストラクタ
	//値の初期化
	Camera_2D::Camera_2D(int _width, int _height)
	{
		Position = XMFLOAT3(0.0, 0, -10);
		Terget = XMFLOAT3(0.0, 0.0, 0.0);
		Projpos = XMFLOAT4(_width, _height, 1.0, 100);

		update();
	}


	//update関数
	//毎フレームごとの値の更新
	void Camera_2D::update()
	{
		View = XMMatrixLookAtLH(XMVectorSet(Position.x, Position.y, Position.z, 1.0f), XMVectorSet(Terget.x, Terget.y, Terget.z, 1.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
		Proj = XMMatrixOrthographicLH(Projpos.x, Projpos.y, Projpos.z, Projpos.w);
	}


	//--------------------------------------------------------------------
}