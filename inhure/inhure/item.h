#pragma once

#include "Mover2D.h"


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

class Item :public Mover2D
{
public:
	Item(InitItemData);
	virtual void update();
	virtual void Draw();

	void terhit(Mover2D*);
	void herhit(Mover2D*);

	F_lib_Mover::Colision_2D* getcol() override;


};

