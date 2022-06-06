#include "Wepon_MissileLunther.h"
#include "MeshM.h"

using namespace F_lib_Mover;
using namespace F_lib_Fremworker;


Wepon_MissileLunther::Wepon_MissileLunther(initWepondata _dat, moverList* _buletlist)
	:Wepon(_dat), buletlist(_buletlist)
{
	dat.R = _dat.R;
	dat.atacklist = _dat.EnemyList;
	dat.speed = 3.0;
	dat.size = 1;
	dat.atack = 3;

	mesh = _dat.R->meshM->getModel(3);
	speed = 2.11f;
	
	cooltime = cooltimeMax = 20;
	countNow = countMax = 0;

}


void Wepon_MissileLunther::Draw()
{
	mesh->setPosition(Position);
	mesh->setangle(angle);
	mesh->RDraw();

}


void Wepon_MissileLunther::ThisAtack()
{
	Wepon::ThisAtack();

	if (cooltime) return;

	if (enemylist->getlistNum() > 0)
	{
		dat.pos = Position;

		int id = 0;
		Mover*ma = enemylist->getlist(id);
		XMFLOAT2 thispos;
		thispos = XMFLOAT2(ma->getthisposition().x, ma->getthisposition().z);
		thispos.x = thispos.x - Position.x;
		thispos.y = thispos.y - Position.z;
		float flen = thispos.x*thispos.x + thispos.y*thispos.y;


		for (int i = 1; i < enemylist->getlistNum(); i++)
		{ 
			ma = enemylist->getlist(i);
			thispos = XMFLOAT2(ma->getthisposition().x, ma->getthisposition().z);
			thispos.x = thispos.x - Position.x;
			thispos.y = thispos.y - Position.z;
			float len = thispos.x*thispos.x + thispos.y*thispos.y;

			if (len < flen)
			{
				id = i;
				flen = len;

			}

		}
		
		ma = enemylist->getlist(id);
		thispos = XMFLOAT2(ma->getthisposition().x, ma->getthisposition().z);
		thispos.x = thispos.x - Position.x;
		thispos.y = thispos.y - Position.z;
		dat.angle = atan2(thispos.x, thispos.y)* 180.0f / 3.14f;//angle.y;

		Mover* m;
		m = new Bullet(dat);
		buletlist->listPush(m);

	}

}
