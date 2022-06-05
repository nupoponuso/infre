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

	mesh = _dat.R->meshM->getModel(3);
	speed = 1.51f;
	
	cooltime = cooltimeMax = 30;
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

	//if (enemylist->getlistNum()>0)
	//{
		dat.pos = Position;

		//Mover*ma = enemylist->getlist(0);
		
		//XMFLOAT2 thisposold = XMFLOAT2(ma->getthisposition().x, ma->getthisposition().z);
		//thisposold.x = thisposold.x - Position.x;
		//thisposold.y = thisposold.y - Position.z;

		dat.angle = angle.y;//atan2(thisposold.x, thisposold.y)* 180.0f / 3.14f;

		Mover* m;
		m = new Bullet(dat);
		buletlist->listPush(m);

	//}

}
