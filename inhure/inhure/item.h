#pragma once

#include "F_lib/include/mover.h"


enum ItemType
{
	Item_Wepon = 0, 
	Item_Epuipment,

	Item_MAX
};

struct InitItemData
{
	F_lib_Fremworker::ResourceManager* R;
	ItemType type;


};

class Item :public F_lib_Mover::Mover
{
public:
	Item(InitItemData);
	virtual void update();
	virtual void Draw();

	void terhit(Mover*);
	void herhit(Mover*);

	F_lib_Mover::Colision_2D* getcol() override;


};

