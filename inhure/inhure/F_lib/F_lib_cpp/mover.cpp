//-------------------------------------------
//
// プレーヤー、弾、敵の仮想クラス 
//		auhor: fujioka tomoya
//		
//
//-------------------------------------------

//インクルード
#include "mover.h"
#include "Colision.h"
#include "ResourceManager.h"


namespace F_lib_Mover 
{
	//Moverクラス-----------------------------------------

	// コンストラクタ：Taskクラスコンストラクタの初期化リスト付き
	//	メンバ変数の初期化　引数：タスクリスト,初期座標xy,角度,スピード,テクスチャマネージャー
	MoverBase::MoverBase(F_lib_Fremworker::ResourceManager* _R)
		: Resource(_R), Alive(true)
	{
		Size = XMFLOAT3(1, 1, 1);
		Angle = XMFLOAT3();

	}

	//-----------------------------------------
	
	//mover用一般関数
	
	float getLockAngle_2D(XMFLOAT2 _posthis, XMFLOAT2 _posterget)
	{
		float angle;
		XMFLOAT2 thispos = _posterget;
		thispos.x = thispos.x - _posthis.x;
		thispos.y = thispos.y - _posthis.y;
		angle = atan2(thispos.x, thispos.y)* 180.0f / 3.14f;

		return angle;
	}

	
	//getlockangle関数
	//第一引数＊の位置から第二引数＊の位置の角度を取得
	//XMFLOAT3 getlockangle_3D(Mover * _this, Mover * _terget)
	//{
	//	if (_terget == nullptr) 
	//		return XMFLOAT3();
	//
	//	return getlockangle_3D(_this->getcol()->box->Pos, _terget);
	//}
	//
	//
	////getlockangle関数
	////第一引数の位置から第二引数の位置の角度を取得
	//XMFLOAT3 getlockangle_3D(XMFLOAT3 _pos, Mover * _terget)
	//{
	//	XMFLOAT3 tergetpos, angle;
	//
	//	tergetpos = _terget->getcol()->box->Pos;
	//	tergetpos = XMFLOAT3(tergetpos.x - _pos.x, tergetpos.y - _pos.y, tergetpos.z - _pos.z);
	//
	//	angle.y = atan2(tergetpos.x, tergetpos.z);
	//	angle.x = atan2(tergetpos.y, hypot(tergetpos.z, tergetpos.x));
	//
	//	angle.y = angle.y * 180.0f / 3.14f;
	//	angle.x = angle.x * 180.0f / 3.14f;
	//	angle.z = 0;
	//
	//	return angle;
	//}
	//
	//-----------------------------------------
}
