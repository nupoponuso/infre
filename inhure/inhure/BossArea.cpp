#include "BossArea.h"

BossArea::BossArea(InitBossData _dat) :Boss(_dat)
{
	stetas.hp = 10000000;

}

BossArea::~BossArea()
{
}

void BossArea::Update()
{
	Boss::Update();
}

void BossArea::Draw()
{
	Boss::Draw();

}

void BossArea::terhit(Mover2D *)
{
}

void BossArea::herhit(Mover2D *)
{
}

F_lib_Mover::Colision_2D * BossArea::getcol()
{
	return nullptr;
}
