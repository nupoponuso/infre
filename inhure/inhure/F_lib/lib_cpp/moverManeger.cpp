//-------------------------------------------
//
//		movermanegerクラス、moverlistクラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//インクルード
#include "moverManeger.h"
#include "ResourceManager.h"
#include "mover.h"



namespace F_lib_Mover
{

	//moverListクラス-----------------------------------------
	
	//コンストラクタ
	//初期化
	moverList::moverList()
	{ }
	
	
	//update関数
	//list内のオブジェクトを管理、更新
	void moverList::update()
	{
		for (auto m : list)
		{
			if (!m->Alive)
			{
				auto iter = std::find(list.begin(), list.end(), m);
				if (iter != list.end())
				{
					std::iter_swap(iter, list.end() - 1);
					list.pop_back();
	
				}
	
			}
			else m->update();
	
		}
	
	}
	
	
	//Draw関数
	//list内のオブジェクトの描画
	void moverList::Draw()
	{
		for (auto m : list)
		{
			m->Draw();
		}
	
	}
	
	
	//Drawshadow関数
	//list内のオブジェクトの影描画
	
	
	//listPush関数
	//listの最後尾に引数のポインタをプッシュ
	void moverList::listPush(F_lib_Mover::Mover* _ins)
	{
		list.push_back(_ins);
	
	}
	
	
	//Ishit関数
	//list内のオブジェクト全てとと引数の当たり判定をする
	bool moverList::Ishit(F_lib_Mover::Mover* _is)
	{
		bool ref = false;
		F_lib_Mover::Colision_2D* Col1, *Col2;
		Col1 = _is->getcol();
	
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i] == _is)
				continue;
	
			Col2 = list[i]->getcol();
			if ((Col1 != nullptr&&Col2 != nullptr) && Col2->ishit(Col1))
			{
				list[i]->herhit(_is);
				_is->terhit(list[i]);

				ref = true;
			}
	
		}
	
		return ref;
	}
	
	
	//-----------------------------------------
	
	//moverManegerクラス-----------------------------------------
	
	//コンストラクタ
	//初期化
	moverManeger::moverManeger(F_lib_Fremworker::ResourceManager* _R) : R(_R)
	{
		dethcount = 0;
	
	}
	
	
	//update関数
	//listの更新とlist内で死んだオブジェクトの数を更新
	void moverManeger::update()
	{
		nownum = list.getlistNum();
		list.update();
	
		if (nownum != list.getlistNum())
			dethcount += nownum - list.getlistNum();
	
	}
	
	
	//Draw関数
	//listの描画
	void moverManeger::Draw()
	{
		list.Draw();
	
	}
	
	
	//alldeth関数
	//list内全てのをaliveを偽して更新する
	void moverManeger::alldeth(int _i)
	{
		int i, j;
		F_lib_Mover::Mover* m;
		j = list.getlistNum();
	
		for (i = _i; i < j; i++)
		{
			m = list.getlist(i);
			m->Alive = false;
		}
	
		list.update();
	
	}
	
	//-----------------------------------------

}