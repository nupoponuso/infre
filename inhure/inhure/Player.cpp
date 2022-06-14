#include "Player.h"

#include "F_lib/include/Mesh_Sprite.h"
#include "RM.h"
#include "MeshM.h"
#include "input.h"

#include "Wepon_MissileLunther.h"
#include "WeponSword.h"
#include "Equipment.h"
#include "item.h"

class Wepon_MissileLunther;

using namespace F_lib_Mover;
using namespace F_lib_Render;

Player::Player(initplayerdata _dat)
	:Mover2D(_dat.R), enemyList(_dat.enemyList), mybList(_dat.bulletList), ebList(_dat.enemybList), itemList(_dat.itemList), oList(_dat.oList)
{
	Position = XMFLOAT3();
	mesh = _dat.R->meshM->getModel(0);
	speed = 1.85f;
	speedRot = 10;//ï˚å¸êßå‰ÇÃéû
	//rotspeed = 4;//ê˘âÒêßå‰ÇÃéû
	
	cpos = Position;
	cpos.y += 150;
	Resource->meshM->getCamera()->setPosition(cpos);
	Resource->meshM->getCamera()->update();

	col = new Colision_2D(Colision_2D::Col_crecle);
	col->getColdata()->size.x = 1;
	
	weponNum = 0;
	
	//åpè≥ÇµÇΩÇ∆Ç´Ç…Ç±Ç±ÇÃÉpÉâÉÅÅ[É^ê›íËÇ»Ç«Çîhê∂ÉNÉâÉXÇ…âfÇ∑
	weponMaxNum = 6;
	wepon = new Wepon*[weponMaxNum];

	chengeWeponNum = mainWeponNum = 1;
	CreateWepon(weponId::Wepon_showd);
	//CreateWepon(Weponid::Wepon_missilelunther);

}

void Player::update()
{
	Move();

	UseWepon();

	cpos = Position;
	cpos.y += 80;

}

void Player::Draw()
{
	Resource->meshM->getCamera()->setPosition(cpos);
	Resource->meshM->getCamera()->update();

	mesh->setPosition(Position);
	mesh->setangle(Angle);
	mesh->setSize(0.01f);
	mesh->RDraw();

	for (int i = 0; i < weponNum; i++)
	wepon[i]->Draw();

}

void Player::terhit(Mover2D *_m)
{
	Item* item;

	switch (_m->getMyid())
	{
	case mover_enemy:

		break;
	case mover_bullet:

		break;
	case mover_item:
		
		item = dynamic_cast<Item*>(_m);
		if (item != nullptr)
		{
			ItemWepon* Iwepon;
			switch (item->getItemtype())
			{
			case Item_Wepon:
				Iwepon = dynamic_cast<ItemWepon*>(item);

				if (CreateWepon(Iwepon->getWeponId()))
					_m->Alive = false;


				break;
			}


		}

		break;
	case mover_obstacle:
		break;
	}
	

}

void Player::herhit(Mover2D *)
{
}

Colision_2D * Player::getcol()
{
	col->getColdata()->pos = XMFLOAT2(Position.x, Position.z);

	return col;
}

void Player::Move()
{
	isMove = true;
	
	//ï˚å¸êßå‰
	if (GetKeyPress(VK_W))
	{
		if (GetKeyPress(VK_A))moveDir = -45;
		else if (GetKeyPress(VK_D)) moveDir = 45;
		else moveDir = 0;
	
	}
	else if (GetKeyPress(VK_S))
	{
		if (GetKeyPress(VK_A)) moveDir = -135;
		else if (GetKeyPress(VK_D)) moveDir = 135;
		else moveDir = 180;
	
	}
	else
	{
		if (GetKeyPress(VK_A)) moveDir = -90;
		else if (GetKeyPress(VK_D)) moveDir = 90;
		else isMove = false;
	
	}
	Angle.y = moveDir;
	
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
	//if (GetKeyPress(VK_A)) Angle.y += -rotspeed;
	//else if (GetKeyPress(VK_D)) Angle.y += rotspeed;
	//else if (!GetKeyPress(VK_W))
	//	ismove = false;

	if (isMove)
	{
		Position.x += speed * sindeg(Angle.y);
		Position.z += speed * cosdeg(Angle.y);

	}

	itemList->Ishit(this);

}


void Player::UseWepon()
{
	//StrengtheningDataPlayer pdataOll;
	//StrengtheningDataPlayer* pdata;

	if (weponNum == weponMaxNum)
	{
		if (GetKeyTrigger(VK_LEFT))
			chengeWeponNum = ((chengeWeponNum + 1) % (weponMaxNum - mainWeponNum)) + mainWeponNum;
		else if (GetKeyTrigger(VK_9))
		{
			delete wepon[chengeWeponNum];
			wepon[chengeWeponNum] = nullptr;

			for (int i = chengeWeponNum; i < weponMaxNum; i++)
				wepon[i] = wepon[i + 1];

			wepon[weponMaxNum] = nullptr;
			weponNum--;

		}

	}
	//else if (GetKeyTrigger(VK_0))
	//{
	//	CreateWepon(Weponid::Wepon_missilelunther);
	//}

	for (auto relic : relicList)
	{
		relic->update();

		//if (relic->getdataP() != nullptr)
		//{
		//	pdata = relic->getdataP();
		//
		//}

	}

	for (int i = 0; i < weponNum; i++)
	{
		wepon[i]->update();

	}


}

bool Player::CreateWepon(weponId _id)
{
	if (weponNum < weponMaxNum)
	{
		initWepondata datInitWepon;
		datInitWepon.p = this;
		datInitWepon.pos = Position;
		datInitWepon.EnemyList = enemyList;
		datInitWepon.R = Resource;
		datInitWepon.pangle = 0;

		switch (_id)
		{
		case Wepon_missilelunther:
			waitWepon = new Wepon_MissileLunther(datInitWepon, mybList);
			break;
		case Wepon_lyzer:
			//waitWepon=new
			break;
		case Wepon_flamethrower:
			//waitWepon=new
			break;
		case Wepon_showd:
			waitWepon = new WeponSword(datInitWepon);
			break;
		case Wepon_boomerang:
			//waitWepon=new
			break;

		}

		wepon[weponNum] = waitWepon;
		waitWepon = nullptr;
		weponNum++;
		return true;

	}
	else return false;
	
}

void Player::CreateRelic()
{

	


}
