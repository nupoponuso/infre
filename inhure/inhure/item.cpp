#include "item.h"

Item::Item(InitItemData _data) :Mover(_data.R, XMFLOAT3(), 0)
{

}

void Item::update()
{
}

void Item::Draw()
{
}

void Item::terhit(Mover *)
{
}

void Item::herhit(Mover *)
{
}

F_lib_Mover::Colision_2D * Item::getcol()
{
	return nullptr;
}
