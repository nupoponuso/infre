//-------------------------------------------
//
//		movermaneger�N���X�Amoverlist�N���X 
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once


//�C���N���[�h
#include <vector>
#include "mover.h"
#include "Colision.h"


namespace F_lib_Mover
{

	//moverList�N���X-----------------------------------------

	//moverList�N���X
	//�N���X�����o
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
	
	//moverManeger�N���X-----------------------------------------
	
	//moverManeger�N���X�@
	//�N���X�����o
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