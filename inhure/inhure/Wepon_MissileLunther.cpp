#include "Wepon_MissileLunther.h"
#include "MeshM.h"
#include "BulletHoming.h"

using namespace F_lib_Mover;
using namespace F_lib_Fremworker;


Wepon_MissileLunther::Wepon_MissileLunther(initWepondata _dat, MoverList* _buletlist)
	:Wepon(_dat), buletlist(_buletlist)
{
	dat.R = _dat.R;
	dat.atacklist = _dat.EnemyList;
	dat.speed = 0.9f;//1.8;
	dat.size = 1;
	dat.atack = 3;

	mesh = _dat.R->meshM->getModel(3);
	speed = 2.11f;
	
	cooltime = cooltimeMax = 5;
	countNow = countMax = 0;

}


void Wepon_MissileLunther::Draw()
{
	mesh->setPosition(Position);
	mesh->setangle(Angle);
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
		Mover2D*ma = enemylist->getlist(id);
		XMFLOAT2 thispos;
		thispos = XMFLOAT2(ma->getPosition().x, ma->getPosition().z);
		thispos.x = thispos.x - Position.x;
		thispos.y = thispos.y - Position.z;
		float flen = thispos.x*thispos.x + thispos.y*thispos.y;

		for (int i = 1; i < enemylist->getlistNum(); i++)
		{ 
			ma = enemylist->getlist(i);
			thispos = XMFLOAT2(ma->getPosition().x, ma->getPosition().z);
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
		dat.angle = Angle.y;
		//getLockAngle_2D(XMFLOAT2(this->getPosition().x, this->getPosition().z), XMFLOAT2(ma->getPosition().x, ma->getPosition().z));

		inithpmingbulletdata data;
		data.data = dat;
		data.terget = ma;
		data.maxrotangle = 10;
		Mover2D* m;
		m = new BulletHoming(data);
		buletlist->listPush(m);

	}

}
