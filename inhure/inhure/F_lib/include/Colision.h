//-------------------------------------------
//
// 　当たり判定クラス |　Colision.cpp　|
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//インクルード
#include "comon.h"


//定数宣言
#define MAX_BBOX (25)


//　当たり判定box用構造体
struct BBox
{
	XMVECTOR Axis[3];
	XMFLOAT3 Size, Center, Pos, size ,Colpos,pos;
	XMMATRIX rot;
	int boneindex;

	BBox()
	{
		Size   = XMFLOAT3(0, 0, 0);
		Center = XMFLOAT3(0, 0, 0); 
		Pos    = XMFLOAT3(0, 0, 0); 
		size   = XMFLOAT3(0, 0, 0); 
		Colpos = XMFLOAT3(0, 0, 0);
		pos    = XMFLOAT3(0, 0, 0);
		Axis[0] = XMVectorSet(1, 0, 0, 0);
		Axis[1] = XMVectorSet(0, 1, 0, 0);
		Axis[2] = XMVectorSet(0, 0, 1, 0);
		boneindex = -1;
	}
	
};



namespace F_lib_Mover 
{

	//　コリジョンクラス
	//　クラスメンバ
	class Colision_3D
	{
	public:
		Colision_3D();
		Colision_3D(int*, int);

		void update();
		bool ishit(Colision_3D*, int _colid = -1);
		void creatCol(XMFLOAT3*, int _id = 0);
		void setPostion(XMFLOAT3 _pos);
		void setangle(XMFLOAT3);
		void setsize(XMFLOAT3);


		BBox* box;
		int Bboxnum;

	private:
		bool ishit(Colision_3D*, int, int);
		bool CompareLenght(BBox* boxA, BBox* boxB, XMVECTOR s, XMVECTOR d);

	};

	struct Coldata_2D
	{
		XMFLOAT2 pos, size;

	};

	class Colision_2D
	{

	public:
		enum Col_Type
		{
			Col_crecle,
			Col_Box,
			Col_Line,

			Col_MAX
		};

		Colision_2D(Col_Type);
		bool ishit(Colision_2D*);
	
		void setdat(Coldata_2D _dat) { dat = _dat; }
		

		Col_Type getType() { return coltype; }
		Coldata_2D* getColdata() { return &dat; }

	private:

		bool ishitCrecle(Colision_2D*);
		bool ishitbox(Colision_2D*);
		bool ishitline(Colision_2D*);

		bool iscreclebox(Colision_2D* _crecle, Colision_2D* _box);
		bool islineline(Colision_2D* _line1, Colision_2D* _line2);
		bool islinecrecle(Colision_2D* _line, Colision_2D* _crecle);
		bool islinebox(Colision_2D* _line, Colision_2D* _box);

		Col_Type coltype;
		Coldata_2D dat;

	};

}