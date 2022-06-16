#include "WeponBoomerang.h"
#include "Enemy.h"

using namespace F_lib_Mover;

WeponBoomerang::WeponBoomerang(initWepondata _dat)
	:Wepon(_dat)
{
	b = _dat.R->meshM->getBillbord();
	col = new Colision_2D(Colision_2D::Col_crecle);
	Size.x = 5;
	col->getColdata()->size.x = Size.x /2;
	atack = 100;

	speed = 1.11f;
	cooltimeNow = cooltimeMax = 60;
	countNow = countMax = 60;

}

void WeponBoomerang::Draw()
{

	b->reset();
	b->setPosition(Position);
	b->setSize(Size.x);
	b->RDraw();

}

void WeponBoomerang::terhit(Mover2D * _m)
{
	//
	if (_m->getMyid() == mover_enemy)
	{
		Enemy* e = dynamic_cast<Enemy*>(_m);
		e->addHp(-atack);

	}

}

F_lib_Mover::Colision_2D * WeponBoomerang::getcol()
{
	col->getColdata()->pos = XMFLOAT2(Position.x, Position.z);

	return col;
}

void WeponBoomerang::move()
{
	if (isMove)
	{
		if (coolTime)
			isMove = false;

		if (countNow > countMax / 2)
		{
			Position.x += speed * sindeg(shotAngle);
			Position.z += speed * cosdeg(shotAngle);
		}
		else Wepon::move();

	}
	else Wepon::move();

}

void WeponBoomerang::ThisAtack()
{
	Wepon::ThisAtack();

	if (!coolTime)
	{
		if (!isMove)
		{
			if (countNow == countMax && enemyList->getlistNum() > 0)
			{
				int id = 0;
				Mover2D*ma = enemyList->getlist(id);
				XMFLOAT2 thispos;
				thispos = XMFLOAT2(ma->getPosition().x, ma->getPosition().z);
				thispos.x = thispos.x - Position.x;
				thispos.y = thispos.y - Position.z;
				float flen = thispos.x*thispos.x + thispos.y*thispos.y;

				for (int i = 1; i < enemyList->getlistNum(); i++)
				{
					ma = enemyList->getlist(i);
					thispos = XMFLOAT2(ma->getPosition().x, ma->getPosition().z);
					thispos.x = thispos.x - Position.x;
					thispos.y = thispos.y - Position.z;
					float len = thispos.x*thispos.x + thispos.y*thispos.y;

					if (len < flen&&ma->Alive)
					{
						id = i;
						flen = len;

					}

				}

				ma = enemyList->getlist(id);
				shotAngle = F_lib_Mover::getLockAngle_2D(XMFLOAT2(p->getPosition().x, p->getPosition().z), XMFLOAT2(ma->getPosition().x, ma->getPosition().z));
				isMove = true;

			}

		}
		else enemyList->Ishit(this);

	}
}
