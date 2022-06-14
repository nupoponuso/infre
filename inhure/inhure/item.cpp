#include "item.h"

#include "MeshM.h"

Item::Item(InitItemData _data) :Mover2D(_data.R), b(_data.R->meshM->getBillbord())
{
	Myid = mover_item;
	Position = _data.pos;
	Size.x = 1;
	col = new F_lib_Mover::Colision_2D(F_lib_Mover::Colision_2D::Col_crecle);
	col->getColdata()->size.x = 10;

}

void Item::update()
{
}

void Item::Draw()
{
	b->setPosition(Position);
	b->setSize(Size.x);
	b->RDraw();
}

//void Item::terhit(Mover2D *)
//{
//}
//
//void Item::herhit(Mover2D *)

F_lib_Mover::Colision_2D * Item::getcol()
{
	col->getColdata()->pos = XMFLOAT2(Position.x, Position.z);

	return col;
}

ItemWepon::ItemWepon(InitItemData _data, weponId _id) :Item(_data)
{
	type= Item_Wepon;
	Id = _id;

}
