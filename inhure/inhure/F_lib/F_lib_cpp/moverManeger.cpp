//-------------------------------------------
//
//		movermaneger�N���X�AmoverList2D�N���X 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//�C���N���[�h
#include "moverManeger.h"
#include "ResourceManager.h"
#include "mover.h"
#include "Colision.h"


namespace F_lib_Mover
{

	////moverList2D�N���X-----------------------------------------
	//
	//
	////update�֐�
	////list���̃I�u�W�F�N�g���Ǘ��A�X�V
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
	////Draw�֐�
	////list���̃I�u�W�F�N�g�̕`��
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
	////Drawshadow�֐�
	////list���̃I�u�W�F�N�g�̉e�`��
	//
	//
	////listPush�֐�
	////list�̍Ō���Ɉ����̃|�C���^���v�b�V��
	//void moverList2D::listPush(MoverBase2D* _ins)
	//{
	//	list.push_back(_ins);
	//
	//}
	//
	//
	////Ishit�֐�
	////list���̃I�u�W�F�N�g�S�ĂƂƈ����̓����蔻�������
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
