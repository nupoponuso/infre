//-------------------------------------------
//
//		movermaneger�N���X�Amoverlist�N���X 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//�C���N���[�h
#include "moverManeger.h"
#include "ResourceManager.h"
#include "mover.h"



namespace F_lib_Mover
{

	//moverList�N���X-----------------------------------------
	
	//�R���X�g���N�^
	//������
	moverList::moverList()
	{ }
	
	
	//update�֐�
	//list���̃I�u�W�F�N�g���Ǘ��A�X�V
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
	
	
	//Draw�֐�
	//list���̃I�u�W�F�N�g�̕`��
	void moverList::Draw()
	{
		for (auto m : list)
		{
			m->Draw();
		}
	
	}
	
	
	//Drawshadow�֐�
	//list���̃I�u�W�F�N�g�̉e�`��
	
	
	//listPush�֐�
	//list�̍Ō���Ɉ����̃|�C���^���v�b�V��
	void moverList::listPush(F_lib_Mover::Mover* _ins)
	{
		list.push_back(_ins);
	
	}
	
	
	//Ishit�֐�
	//list���̃I�u�W�F�N�g�S�ĂƂƈ����̓����蔻�������
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
	
	//moverManeger�N���X-----------------------------------------
	
	//�R���X�g���N�^
	//������
	moverManeger::moverManeger(F_lib_Fremworker::ResourceManager* _R) : R(_R)
	{
		dethcount = 0;
	
	}
	
	
	//update�֐�
	//list�̍X�V��list���Ŏ��񂾃I�u�W�F�N�g�̐����X�V
	void moverManeger::update()
	{
		nownum = list.getlistNum();
		list.update();
	
		if (nownum != list.getlistNum())
			dethcount += nownum - list.getlistNum();
	
	}
	
	
	//Draw�֐�
	//list�̕`��
	void moverManeger::Draw()
	{
		list.Draw();
	
	}
	
	
	//alldeth�֐�
	//list���S�Ă̂�alive���U���čX�V����
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