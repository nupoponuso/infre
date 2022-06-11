#include "item.h"

Item::Item(InitItemData _data) :Mover2D(_data.R)
{

}

void Item::update()
{
}

void Item::Draw()
{
}

void Item::terhit(Mover2D *)
{
}

void Item::herhit(Mover2D *)
{
}

F_lib_Mover::Colision_2D * Item::getcol()
{
	return nullptr;
}
