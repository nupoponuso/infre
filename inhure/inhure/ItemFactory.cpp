

//�C���N���[�h
#include "ItemFactory.h"
#include <random>
#include "item.h"


//�@�R���X�g���N�^
//�@���X�g�̐ݒ�
ItemFactory::ItemFactory(F_lib_Fremworker::ResourceManager*_R, MoverList * _list) :list(_list)
{
	Data.R = _R;

}


//�@Create�֐�
//�@�����_���Ő������s��
void ItemFactory::Create(XMFLOAT3 _pos)
{
	Data.pos = _pos;

	//std::random_device rnd;
	//std::mt19937 mt(rnd());
	//std::uniform_int_distribution<> rand(0, Item_MAX);
	//
	//int id = rand(mt);
	//
	//switch (id)
	//{
	//case Item_Wepon:
	CreateWepon();
	//	break;
	//case Item_Epuipment:
	//	CreateEpuipment();
	//	break;
	//default:
	//	break;
	//
	//}
	
}


//
//
void ItemFactory::CreateWepon()
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rand(0, Wepon_MAX);
	
	list->listPush(new ItemWepon(Data, weponId(rand(mt))));

}


//
//
void ItemFactory::CreateEpuipment()
{
}
