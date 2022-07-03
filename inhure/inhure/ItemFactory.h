

#pragma once

//インクルード
#include "item.h"


//　ItemFactoryクラス
//　アイテムをランダムに作成してリストに登録する
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

