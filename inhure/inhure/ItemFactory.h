

#pragma once

//�C���N���[�h
#include "item.h"


//�@ItemFactory�N���X
//�@�A�C�e���������_���ɍ쐬���ă��X�g�ɓo�^����
class ItemFactory
{
public:
	ItemFactory(F_lib_Fremworker::ResourceManager*, class MoverList*);

	void Create(XMFLOAT3);

private:
	void CreateWepon();
	void CreateEpuipment();

	class MoverList* list;
	InitItemData Data;

};

