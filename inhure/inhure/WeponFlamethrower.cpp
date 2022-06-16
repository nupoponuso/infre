#include "WeponFlamethrower.h"

#include <random>

WeponFlamethrower::WeponFlamethrower(initWepondata _dat, MoverList*_blist) 
	: Wepon(_dat), buletlist(_blist)
{
	b = Resource->meshM->getBillbord();
	dat.R = Resource;
	dat.atacklist = _dat.EnemyList;
	dat.speed = 0.4;
	dat.size = 1;
	dat.atack = 10;

	Size.x = 2.5f;
	speed = 3;

	rotspeed = 0;

	cooltimeNow = cooltimeMax = 60;
	countNow = countMax = 60;
}

void WeponFlamethrower::Draw()
{
	b->reset();
	b->setPosition(Position);
	b->setSize(Size.x);
	b->RDraw();
}

void WeponFlamethrower::move()
{
	Wepon::move();
	
}

void WeponFlamethrower::ThisAtack()
{
	Wepon::ThisAtack();

	if (!coolTime)
	{
		if (countNow % 2 == 0) 
		{
			std::random_device rnd;
			std::mt19937 mt(rnd());
			std::uniform_int_distribution<> rand100(-90, 90);

			dat.pos = Position;
			dat.angle = Angle.y + (float)rand100(mt);
			Bullet* b = new Bullet(dat);
			buletlist->listPush(b);

		}

	}


}
