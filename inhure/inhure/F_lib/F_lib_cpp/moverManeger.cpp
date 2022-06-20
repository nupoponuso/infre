//-------------------------------------------
//
//		movermanegerクラス、moverList2Dクラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//インクルード
#include "moverManeger.h"
#include "ResourceManager.h"
#include "mover.h"
#include "Colision.h"


namespace F_lib_Mover
{

	////moverList2Dクラス-----------------------------------------
	//
	//
	////update関数
	////list内のオブジェクトを管理、更新
	//void moverList2D::update()
	//{
	//	for (auto m : list)
	//	{
	//		if (!m->Alive)
	//		{
	//			auto iter = std::find(list.begin(), list.end(), m);
	//			if (iter != list.end())
	//			{
	//				std::iter_swap(iter, list.end() - 1);
	//				list.pop_back();
	//
	//			}
	//
	//		}
	//		else m->update();
	//
	//	}
	//
	//}
	//
	//
	////Draw関数
	////list内のオブジェクトの描画
	//void moverList2D::Draw()
	//{
	//	for (auto m : list)
	//	{
	//		m->Draw();
	//	}
	//
	//}
	//
	//
	////Drawshadow関数
	////list内のオブジェクトの影描画
	//
	//
	////listPush関数
	////listの最後尾に引数のポインタをプッシュ
	//void moverList2D::listPush(MoverBase2D* _ins)
	//{
	//	list.push_back(_ins);
	//
	//}
	//
	//
	////Ishit関数
	////list内のオブジェクト全てとと引数の当たり判定をする
	//bool moverList2D::Ishit(MoverBase2D* _is)
	//{
	//	bool ref = false;
	//	F_lib_Mover::Colision_2D* Col1, *Col2;
	//	Col1 = _is->getcol();
	//
	//	for (int i = 0; i < list.size(); i++)
	//	{
	//		if (list[i] == _is)
	//			continue;
	//
	//		Col2 = list[i]->getcol();
	//		if ((Col1 != nullptr&&Col2 != nullptr) && Col2->ishit(Col1))
	//		{
	//			list[i]->herhit(_is);
	//			_is->terhit(list[i]);

	//			ref = true;
	//		}
	//
	//	}
	//
	//	return ref;
	//}
	//
	//
	////-----------------------------------------
	
}
