//-------------------------------------------
//
// プレーヤー、弾、敵の仮想クラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//インクルード
#include "comon.h"
#include "ResourceManager.h"
#include "Colision.h"


namespace F_lib_Mover
{

	//　Moverクラス 
	//	クラスメンバ
	class MoverBase
	{
	public:
		//コンストラクタ
		MoverBase(F_lib_Fremworker::ResourceManager*); //座標、角度などの初期化

		//メンバ関数
		virtual void update() = 0;
		virtual void Draw() = 0;
		
		//ゲッター
		XMFLOAT3  getPosition() { return Position; }
		XMFLOAT3  getSize() { return Size; }
		XMFLOAT3  getAngle() { return Angle; }

		bool	 Alive;			//生死判定

	protected:
		//メンバ変数
		F_lib_Fremworker::ResourceManager* Resource;

		XMFLOAT3 Position;		//座標
		XMFLOAT3 Size;			//サイズ
		XMFLOAT3 Angle;			//角度

		bool hit;

	};

	//-----------------------------------------

	//mover用一般関数
	float getLockAngle_2D(XMFLOAT2 _posthis, XMFLOAT2 _posterget);

}



//getlockangle関数　
//第一引数から第二引数の角度を取得　引数：　見る人,ターゲット
//XMFLOAT3 getlockangle(Mover* _this,Mover* _terget);

//getlockangle関数　
//第一引数から第二引数の角度を取得　引数：　位置,ターゲット
//XMFLOAT3 getlockangle(XMFLOAT3 _pos, Mover* _terget);
