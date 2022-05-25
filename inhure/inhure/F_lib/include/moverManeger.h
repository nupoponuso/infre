//-------------------------------------------
//
//		movermanegerクラス、moverlistクラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once


//インクルード
#include <vector>
#include "mover.h"
#include "Colision.h"


namespace F_lib_Mover
{

	//moverListクラス-----------------------------------------

	//moverListクラス
	//クラスメンバ
	class moverList
	{
	public:
		moverList();
	
		void update();
		void Draw();
	
		void listPush(F_lib_Mover::Mover*);
		bool Ishit(F_lib_Mover::Mover*);
	
		F_lib_Mover::Mover* getlist(int _id) { return list[_id]; }
	
		int getlistNum() { return (int)list.size(); }
	
	protected:
		std::vector<F_lib_Mover::Mover*> list;
	
	};
	
	//-----------------------------------------
	
	//moverManegerクラス-----------------------------------------
	
	//moverManegerクラス　
	//クラスメンバ
	class moverManeger
	{
	public:
		moverManeger(F_lib_Fremworker::ResourceManager*);
	
		virtual void update();
		void Draw();
	
		void alldeth(int _i = 0);
		moverList* getlist() { return &list; }
		int getdethcount() { return dethcount; }
	
	protected:
		F_lib_Fremworker::ResourceManager* R;
		moverList list;
		int dethcount, nownum;
	
	};

	//-----------------------------------------

}