#pragma once

#include "Mover2D.h"
#include "Wepon.h"
#include "Equipment.h"
#include "F_lib/include/Mesh_billbord.h"


enum ItemType
{
	Item_Wepon = 0, 
	Item_Epuipment,

	Item_MAX
};

struct InitItemData
{
	F_lib_Fremworker::ResourceManager* R;
	XMFLOAT3 pos;

};

class Item :public Mover2D
{
public:
	Item(InitItemData);
	virtual void update();
	virtual void Draw();

	void terhit(Mover2D*) {}
	void herhit(Mover2D*) {}

	F_lib_Mover::Colision_2D* getcol() override;
	ItemType getItemtype() { return type; }

protected:
	F_lib_Render::Mesh_billbord* b;
	ItemType type;

	
};

class ItemWepon :public Item
{
public:
	ItemWepon(InitItemData,weponId);
	
	weponId getWeponId() { return Id; }

protected:
	weponId Id;

};
