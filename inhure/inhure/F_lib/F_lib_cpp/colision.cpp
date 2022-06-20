//-------------------------------------------
//
// 　当たり判定クラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//インクルード
#include "Colision.h"
#include "comon.h"
#include <math.h>

namespace F_lib_Mover
{
	//コンストラクタ
	//引数無し
	Colision_3D::Colision_3D()
	{
		Bboxnum = 1;
		box = new BBox();

	}


	//コンストラクタ
	//引数あり　スキンメッシュOBB用の情報の生成現在開発中止
	Colision_3D::Colision_3D(int * _index, int _boxnum)
	{
		Bboxnum = 1 + _boxnum;
		box = new BBox[Bboxnum];
		for (int i = 1; i < Bboxnum; i++)
			box[i].boneindex = _index[i - 1];

	}


	//createCol関数
	//モデルから渡された最大最小それぞれの商店情報からOBB用のデータの作成
	void Colision_3D::creatCol(XMFLOAT3* _dat, int _id)
	{
		XMFLOAT3 Half;
		Half = XMFLOAT3((_dat[1].x - _dat[0].x) / 2.0f, (_dat[1].y - _dat[0].y) / 2.0f, (_dat[1].z - _dat[0].z) / 2.0f);
		box->Center = XMFLOAT3(_dat[0].x + Half.x, _dat[0].y + Half.y, _dat[0].z + Half.z);

		box->size.x = Half.x;
		box->size.y = Half.y;
		box->size.z = Half.z;

	}


	//ishit関数
	//引数　：Colision＊、OBBボックスのインデックス
	bool Colision_3D::ishit(Colision_3D* _col, int _colid)
	{
		if (this == nullptr)return false;

		update();
		_col->update();

		int i;

		if (_colid == -1)
		{
			for (i = 0; i < Bboxnum; i++)
			{
				for (int j = 0; j < _col->Bboxnum; j++)
				{
					if (ishit(_col, i, j)) return true;
				}
			}
		}
		else
		{
			for (i = 0; i < Bboxnum; i++)
			{
				if (ishit(_col, i, _colid)) return true;
			}
		}

		return false;
	}


	//update関数
	//モデル描画の前に呼ばれて当たり判定用情報の更新
	void Colision_3D::update()
	{
		box->Pos.x = box->pos.x + box->Colpos.x;
		box->Pos.y = box->pos.y + box->Colpos.y;
		box->Pos.z = box->pos.z + box->Colpos.z;

		box->Axis[0] = XMVectorSet(1, 0, 0, 1);
		box->Axis[1] = XMVectorSet(0, 1, 0, 1);
		box->Axis[2] = XMVectorSet(0, 0, 1, 1);

		for (int j = 0; j < 3; j++)
		{
			box->Axis[j] = XMVector3TransformCoord(box->Axis[j], box->rot);
			box->Axis[j] = XMVector3Normalize(box->Axis[j]);
		}

	}


	//setposition 関数
	//当たり判定用情報の意図的更新関数
	void Colision_3D::setPostion(XMFLOAT3 _pos)
	{
		if (this == nullptr)return;

		box->pos = _pos;

		box->Pos.x = box->pos.x + box->Colpos.x;
		box->Pos.y = box->pos.y + box->Colpos.y;
		box->Pos.z = box->pos.z + box->Colpos.z;

	}


	//setangle 関数
	//当たり判定用情報の意図的更新
	//boneの影響があるもでるには使用禁止
	void Colision_3D::setangle(XMFLOAT3 angle)
	{
		if (this == nullptr)return;

		box->rot = XMMatrixIdentity();
		box->rot *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(angle.x), XMConvertToRadians(angle.y), XMConvertToRadians(angle.z));
	}



	//setasize 関数
	//当たり判定用情報の意図的更新
	void Colision_3D::setsize(XMFLOAT3 _Size)
	{
		if (this == nullptr)return;

		box->Size.x = box->size.x * _Size.x;
		box->Size.y = box->size.y * _Size.y;
		box->Size.z = box->size.z * _Size.z;

		box->Colpos.x = box->Center.x * _Size.x;
		box->Colpos.y = box->Center.y * _Size.y;
		box->Colpos.z = box->Center.z * _Size.z;

	}


	//ishit関数
	//当たり判定
	bool Colision_3D::ishit(Colision_3D * _col, int _myid, int _id)
	{

		if (!((box->Pos.x + box->Size.x >= _col->box->Pos.x - _col->box->Size.x && box->Pos.x - box->Size.x <= _col->box->Pos.x + _col->box->Size.x)
			&& (box->Pos.y + box->Size.y >= _col->box->Pos.y - _col->box->Size.y && box->Pos.y - box->Size.y <= _col->box->Pos.y + _col->box->Size.y)
			&& (box->Pos.z + box->Size.z >= _col->box->Pos.z - _col->box->Size.z && box->Pos.z - box->Size.z <= _col->box->Pos.z + _col->box->Size.z)))
			return false;

		int i, j;
		XMVECTOR Separate, Distanse;
		Distanse = XMVectorSet(_col->box->Pos.x - box->Pos.x, _col->box->Pos.y - box->Pos.y, _col->box->Pos.z - box->Pos.z, 1);

		for (i = 0; i < 3; i++)
		{
			if (!CompareLenght(box, _col->box, box->Axis[i], Distanse)) return false;
			if (!CompareLenght(box, _col->box, _col->box->Axis[i], Distanse)) return false;

		}

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				Separate = XMVector3Cross(box->Axis[i], _col->box->Axis[j]);
				if (!CompareLenght(box, _col->box, Separate, Distanse)) return false;
			}

		}

		return true;

		/*Distanse = XMVectorSet(_col->box[_id].Pos.x - box[_myid].Pos.x, _col->box[_id].Pos.y - box[_myid].Pos.y, _col->box[_id].Pos.z - box[_myid].Pos.z, 1);

		for (i = 0; i < 3; i++)
		{
			if (!CompareLenght(&box[_myid], &_col->box[_id],	 box[_myid].Axis[i], Distanse)) return false;
			if (!CompareLenght(&box[_myid], &_col->box[_id], _col->box[_id].Axis[i], Distanse)) return false;

		}

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				Separate = XMVector3Cross(box[_myid].Axis[i], _col->box[_id].Axis[j]);
				if (!CompareLenght(&box[_myid], &_col->box[_id], Separate, Distanse)) return false;
			}

		}

		return true;*/
	}


	//CompareLenght関数
	//保持している情報から軸に平行な影を取り出して比較する
	bool Colision_3D::CompareLenght(BBox * boxA, BBox * boxB, XMVECTOR s, XMVECTOR d)
	{
		float Distance, ShadowA, ShadowB;
		XMFLOAT3 S;
		XMVECTOR Se = XMVector3Normalize(s);

		XMStoreFloat(&Distance, XMVector3Dot(d, Se));
		ShadowA = float(fabs(Distance));
		ShadowA = ShadowB = 0;

		XMStoreFloat(&S.x, XMVector3Dot(boxA->Axis[0], Se)* boxA->Size.x);
		XMStoreFloat(&S.y, XMVector3Dot(boxA->Axis[1], Se)* boxA->Size.y);
		XMStoreFloat(&S.z, XMVector3Dot(boxA->Axis[2], Se)* boxA->Size.z);

		ShadowA = float(fabs(S.x) + fabs(S.y) + fabs(S.z));

		XMStoreFloat(&S.x, XMVector3Dot(boxB->Axis[0], Se)* boxB->Size.x);
		XMStoreFloat(&S.y, XMVector3Dot(boxB->Axis[1], Se)* boxB->Size.y);
		XMStoreFloat(&S.z, XMVector3Dot(boxB->Axis[2], Se)* boxB->Size.z);

		ShadowB = float(fabs(S.x) + fabs(S.y) + fabs(S.z));

		if (Distance > ShadowA + ShadowB) return false;

		return true;

	}

//---------------------------------------------------------


	//コンストラクタ
	Colision_2D::Colision_2D(Col_Type _mytype)
	{
		coltype = _mytype;
		
	}


	//ishit関数
	//
	bool Colision_2D::ishit(Colision_2D * _col)
	{
		if (_col == this || _col == nullptr) return false;

		switch (coltype)
		{
		case F_lib_Mover::Colision_2D::Col_crecle:
			return ishitCrecle(_col);

			break;
		case F_lib_Mover::Colision_2D::Col_Box:
			return ishitbox(_col);

			break;
		case F_lib_Mover::Colision_2D::Col_Line:
			return ishitline(_col);
			break;

		default:
			return false;
			break;
		}
	}


	//ishitCreacle関数
	//
	bool Colision_2D::ishitCrecle(Colision_2D * _col)
	{
		bool ref =false;
		XMFLOAT2 colpos(_col->dat.pos.x - this->dat.pos.x, _col->dat.pos.y - this->dat.pos.y);

		switch (_col->getType())
		{
		case F_lib_Mover::Colision_2D::Col_crecle:

			float len,r;

			len = colpos.x*colpos.x + colpos.y*colpos.y;
			r = _col->dat.size.x + this->dat.size.x;
			r = r * r;

			if (len < r) ref = true;

			break;
		case F_lib_Mover::Colision_2D::Col_Box:
			ref = iscreclebox(this,_col);

			break;
		case F_lib_Mover::Colision_2D::Col_Line:
			ref = islinecrecle(_col, this);

			break;
		}

		return ref;
	}


	//ishitbox関数
	//
	bool Colision_2D::ishitbox(Colision_2D * _col)
	{
		bool ref = false;

		switch (_col->getType())
		{
		case F_lib_Mover::Colision_2D::Col_Box:

			if (this->dat.pos.x + this->dat.size.x >= _col->dat.pos.x - _col->dat.size.x
			 && this->dat.pos.x - this->dat.size.x <= _col->dat.pos.x + _col->dat.size.x)
			{
				if (this->dat.pos.y + this->dat.size.y >= _col->dat.pos.y - _col->dat.size.y
				 && this->dat.pos.y - this->dat.size.y <= _col->dat.pos.y + _col->dat.size.y)
					ref = true;
				
			}

			break;
		case F_lib_Mover::Colision_2D::Col_crecle:
			ref = iscreclebox(_col, this);

			break;
		case F_lib_Mover::Colision_2D::Col_Line:
			ref = islinebox(_col, this);

			break;
		}

		return ref;
	}


	//ishitline関数
	//
	bool Colision_2D::ishitline(Colision_2D * _col)
	{
		bool ref = false;

		switch (_col->getType())
		{
		case F_lib_Mover::Colision_2D::Col_Line:
			

			break;
		case F_lib_Mover::Colision_2D::Col_crecle:
			ref = islinecrecle(this, _col);

			break;
		case F_lib_Mover::Colision_2D::Col_Box:
			ref = islinebox(this, _col);

			break;
		}

		return ref;
	}


	//iscreclebox関数
	//円とboxの当たり判定
	bool Colision_2D::iscreclebox(Colision_2D* _crecle, Colision_2D* _box)
	{
		XMFLOAT2 boxpos[2];
		
		boxpos[0] = XMFLOAT2(_box->dat.pos.x - _box->dat.size.x, _box->dat.pos.y - _box->dat.size.y);//Left,top
		boxpos[1] = XMFLOAT2(_box->dat.pos.x + _box->dat.size.x, _box->dat.pos.y + _box->dat.size.y);//right,bottom
		
		if ((boxpos[0].x - _crecle->dat.size.x > _crecle->dat.pos.x) || (boxpos[1].x + _crecle->dat.size.x < _crecle->dat.pos.x)
		  ||(boxpos[0].y - _crecle->dat.size.x > _crecle->dat.pos.y) || (boxpos[1].y + _crecle->dat.size.x < _crecle->dat.pos.y))
			return false;

		float r[4],cr;

		for (int i = 0; i < 4; i += 2)
		{
			r[i]	 = boxpos[(i == 0) ? 0 : 1].x - _crecle->dat.pos.x;
			r[i + 1] = boxpos[(i == 0) ? 0 : 1].y - _crecle->dat.pos.y;
		
		}
		cr = _crecle->dat.size.x*_crecle->dat.size.x;

		if (boxpos[0].x > _crecle->dat.pos.x && boxpos[0].y > _crecle->dat.pos.y && !((r[0] * r[0]) + (r[1] * r[1]) < cr))
			return false;					  

		if (boxpos[1].x < _crecle->dat.pos.x && boxpos[0].y > _crecle->dat.pos.y && !((r[2] * r[2]) + (r[1] * r[1]) < cr))
			return false;					    

		if (boxpos[0].x > _crecle->dat.pos.x && boxpos[1].y < _crecle->dat.pos.y && !((r[0] * r[0]) + (r[3] * r[3]) < cr))
			return false;					    

		if (boxpos[1].x < _crecle->dat.pos.x && boxpos[1].y < _crecle->dat.pos.y && !((r[2] * r[2]) + (r[3] * r[3]) < cr))
			return false;

		return true;
	}

	bool Colision_2D::islineline(Colision_2D * _line1, Colision_2D * _line2)
	{
		//bool LineAndLine(float A1x, float A1y, float A2x, float A2y, float B1x, float B1y, float B2x, float B2y) {
		//	{
		//		const float baseX = B2x - B1x;
		//		const float baseY = B2y - B1y;
		//		const float sub1X = A1x - B1x;
		//		const float sub1Y = A1y - B1y;
		//		const float sub2X = A2x - B1x;
		//		const float sub2Y = A2y - B1y;
		//
		//		const float bs1 = baseX * sub1Y - baseY * sub1X;
		//		const float bs2 = baseX * sub2Y - baseY * sub2X;
		//		const float re = bs1 * bs2;
		//		if (re > 0) {
		//			return false;
		//		}
		//	}
		//	{
		//		const float baseX = A2x - A1x;
		//		const float baseY = A2y - A1y;
		//		const float sub1X = B1x - A1x;
		//		const float sub1Y = B1y - A1y;
		//		const float sub2X = B2x - A1x;
		//		const float sub2Y = B2y - A1y;
		//
		//		const float bs1 = baseX * sub1Y - baseY * sub1X;
		//		const float bs2 = baseX * sub2Y - baseY * sub2X;
		//		const float re = bs1 * bs2;
		//		if (re > 0) {
		//			return false;
		//		}
		//	}
			return true;
		//}
	}


	//
	//
	bool Colision_2D::islinecrecle(Colision_2D * _line, Colision_2D * _crecle)
	{
		XMFLOAT2 center_stert, center_end, stert_end,normal;
		float distanse;

		center_stert.x = _crecle->dat.pos.x - _line->dat.pos.x;
		center_stert.y = _crecle->dat.pos.y - _line->dat.pos.y;
		
		center_end.x = _crecle->dat.pos.x - _line->dat.size.x;
		center_end.y = _crecle->dat.pos.y - _line->dat.size.y;

		stert_end.x = _line->dat.size.x - _line->dat.pos.x;
		stert_end.y = _line->dat.size.y - _line->dat.pos.y;

		distanse = sqrtf((stert_end.x*stert_end.x) + (stert_end.y*stert_end.y));

		if (distanse > 0.0f)
		{
			normal.x = stert_end.x / distanse;
			normal.y = stert_end.y / distanse;

		}
		else normal = XMFLOAT2();
		
		distanse = center_stert.x * normal.y - normal.x * center_stert.y;

		if (fabs(distanse) < _crecle->dat.size.x)
		{
			float dot1, dot2;
			dot1 = center_stert.x*stert_end.x + center_stert.y*stert_end.y;
			dot2 = center_end.x*stert_end.x + center_end.y*stert_end.y;

			if (dot1*dot2 <= 0.0f) return true;
			else 
			{
				dot1 = sqrtf((center_stert.x* center_stert.x) + (center_stert.y*center_stert.y));
				dot2 = sqrtf((center_end.x* center_end.x) + (center_end.y*center_end.y));
				
				if (dot1 < _crecle->dat.size.x || dot2 < _crecle->dat.size.x)
					return true;

			}

		}

		return false;
	}


	//
	//
	bool Colision_2D::islinebox(Colision_2D * _line, Colision_2D * _box)
	{
		return false;
	}

//---------------------------------------------------------

}