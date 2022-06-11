#include "Player.h"

#include "F_lib/include/Mesh_Sprite.h"
#include "RM.h"
#include "MeshM.h"
#include "input.h"

#include "Wepon_MissileLunther.h"
#include "WeponSword.h"

class Wepon_MissileLunther;

using namespace F_lib_Mover;
using namespace F_lib_Render;

Player::Player(initplayerdata _dat)
	:Mover2D(_dat.R), enemylist(_dat.enemylist), myblist(_dat.buletlist), eblist(_dat.ebuletlist)
{
	speed = 1.85f;
	WeponMaxNum = 5;
	//rotspeed = 10;//ï˚å¸êßå‰ÇÃéû
	rotspeed = 4;//ê˘âÒêßå‰ÇÃéû
	mesh = _dat.R->meshM->getModel(0);
	
	Position = XMFLOAT3();

	cpos = Position;
	cpos.y += 150;
	Resource->meshM->getCamera()->setPosition(cpos);
	Resource->meshM->getCamera()->update();

	col = new Colision_2D(Colision_2D::Col_crecle);
	col->getColdata()->size.x = 1;

	initWepondata dat;
	dat.p = this;
	dat.pos = Position;
	dat.EnemyList = enemylist;
	dat.R = Resource;
	dat.pangle =0;
	
	//wepon[0] = new WeponSword(dat);

	for (int i = 0; i < WeponMaxNum; i++)
	{
		dat.pangle += 90;
		dat.pos.x =Position.x  + 10*sindeg(i*90);
		dat.pos.z = Position.z + 10 * cosdeg(i * 90);
		
		wepon[i] = new Wepon_MissileLunther(dat, myblist);
	
	}

}

void Player::update()
{

	move();

	cpos = Position;
	cpos.y += 80;

	for(int i=0;i<WeponMaxNum;i++)
	wepon[i]->update();

}

void Player::Draw()
{
	Resource->meshM->getCamera()->setPosition(cpos);
	Resource->meshM->getCamera()->update();

	mesh->setPosition(Position);
	mesh->setangle(Angle);
	mesh->setSize(0.01f);
	mesh->RDraw();
	for (int i = 0; i < WeponMaxNum; i++)
	wepon[i]->Draw();
}

void Player::terhit(Mover2D *)
{
}

void Player::herhit(Mover2D *)
{
}

Colision_2D * Player::getcol()
{
	col->getColdata()->pos = XMFLOAT2(Position.x, Position.z);

	return col;
}

void Player::move()
{
	ismove = true;
	
	//ï˚å¸êßå‰
	//if (GetKeyPress(VK_W))
	//{
	//	if (GetKeyPress(VK_A))movedir = -45;
	//	else if (GetKeyPress(VK_D)) movedir = 45;
	//	else movedir = 0;
	//
	//}
	//else if (GetKeyPress(VK_S))
	//{
	//	if (GetKeyPress(VK_A)) movedir = -135;
	//	else if (GetKeyPress(VK_D)) movedir = 135;
	//	else movedir = 180;
	//
	//}
	//else
	//{
	//	if (GetKeyPress(VK_A)) movedir = -90;
	//	else if (GetKeyPress(VK_D)) movedir = 90;
	//	else ismove = false;
	//
	//}
	//
	//if (ismove)
	//{
	//	if (movedir < 0)
	//	{
	//		if ((movedirold > 0 && movedir < 0)|| (movedirold < 0 && movedir > 0))
	//			movedir += 360;
	//		
	//	}
	//
	//	 float addmovedir = movedir - Angle.y;
	//
	//	if (addmovedir > 0.1 || addmovedir < -0.1)
	//	{
	//		addmovedir = (addmovedir > 0) ? rotspeed : -rotspeed;
	//		Angle.y += addmovedir;
	//
	//	}
	//	if (movedirold != movedir)
	//		movedirold = movedir;
	//}
	
	//ê˘âÒêßå‰
	if (GetKeyPress(VK_A)) Angle.y += -rotspeed;
	else if (GetKeyPress(VK_D)) Angle.y += rotspeed;
	else if (!GetKeyPress(VK_W))
		ismove = false;

	


	if (ismove)
	{
		Position.x += speed * sindeg(Angle.y);
		Position.z += speed * cosdeg(Angle.y);

	}


}

void Player::atack()
{

}
