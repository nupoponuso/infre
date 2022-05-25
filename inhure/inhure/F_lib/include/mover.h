//-------------------------------------------
//
// プレーヤー、弾、敵の仮想クラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//インクルード
#include "comon.h"
#include "Mesh_Sprite.h"
#include "ResourceManager.h"
#include "Colision.h"
//#include "moverManeger.h"

//	構造体
//	テクスチャアニメーション用構造体
//typedef struct
//{
//	int nPatNo;
//	int nCount;
//}ANIM_PAT;


//移動方向用enum
enum mover_id
{
	mover_player = 0,
	mover_bullet,
	mover_enemy,
	mover_Obstacle,

	mover_max
};



namespace F_lib_Mover
{

	//　Moverクラス 
	//	クラスメンバ
	class Mover
	{
	public:
		//コンストラクタ
		Mover(F_lib_Fremworker::ResourceManager*, XMFLOAT3 _angle, float _speed); //座標、角度などの初期化

		//メンバ関数
		virtual void update() = 0;
		virtual void Draw() = 0;
		virtual void terhit(Mover*) = 0;
		virtual void herhit(Mover*) = 0;

		void addhp(int _add);

		void sethit(bool _f = false, int _count = 0) { hit = _f; hitcount = _count; }

		//ゲッター
		XMFLOAT3  getthisposition() { return Position; }
		XMFLOAT3  getthisSize() { return Size; }
		XMFLOAT3  getangle() { return angle; }
		virtual F_lib_Mover::Colision_2D* getcol();

		mover_id getmyid() { return myid; }
		int  gethp()	   { return hp; }
		int  getmaxhp()    { return Maxhp; }
		int  getatack()    { return atack; }
		bool gethit()      { return hit; }

		bool	 Alive;			//生死判定

	protected:
		//メンバ変数
		F_lib_Fremworker::ResourceManager* Resource;
		F_lib_Mover::Colision_2D* col;
	
		mover_id myid;

		XMFLOAT3 Position;		//座標
		XMFLOAT3 Size;			//サイズ
		XMFLOAT3 angle;			//角度
		float	 speed;			//スピード

		int hp, Maxhp, atack, hitcount;
		bool hit;

	};

}

//-----------------------------------------

//mover用一般関数

//getlockangle関数　
//第一引数から第二引数の角度を取得　引数：　見る人,ターゲット
//XMFLOAT3 getlockangle(Mover* _this,Mover* _terget);

//getlockangle関数　
//第一引数から第二引数の角度を取得　引数：　位置,ターゲット
//XMFLOAT3 getlockangle(XMFLOAT3 _pos, Mover* _terget);
