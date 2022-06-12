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
	:Mover2D(_dat.R), enemylist(_dat.enemylist), myblist(_dat.buletlist), eblist(_dat.ebuletlist), ItemList(_dat.ItemList), Olist(_dat.Olist)
{
	Position = XMFLOAT3();
	mesh = _dat.R->meshM->getModel(0);
	speed = 1.85f;
	rotspeed = 10;//ï˚å¸êßå‰ÇÃéû
	//rotspeed = 4;//ê˘âÒêßå‰ÇÃéû
	
	cpos = Position;
	cpos.y += 150;
	Resource->meshM->getCamera()->setPosition(cpos);
	Resource->meshM->getCamera()->update();

	col = new Colision_2D(Colision_2D::Col_crecle);
	col->getColdata()->size.x = 1;
	

	//åpè≥ÇµÇΩÇ∆Ç´Ç…Ç±Ç±ÇÃÉpÉâÉÅÅ[É^ê›íËÇ»Ç«Çîhê∂ÉNÉâÉXÇ…âfÇ∑
	WeponNum = 2;
	WeponMaxNum = 6;
	wepon = new Wepon*[WeponMaxNum];

	ChengeWeponNum = MainWeponNum = 2;
	CreateWepon(Weponid::Wepon_showd);
	CreateWepon(Weponid::Wepon_missilelunther);

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

	for (int i = MainWeponNum; i < WeponNum; i++)
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
	ismove = true;
	
	//ï˚å¸êßå‰
	if (GetKeyPress(VK_W))
	{
		if (GetKeyPress(VK_A))movedir = -45;
		else if (GetKeyPress(VK_D)) movedir = 45;
		else movedir = 0;
	
	}
	else if (GetKeyPress(VK_S))
	{
		if (GetKeyPress(VK_A)) movedir = -135;
		else if (GetKeyPress(VK_D)) movedir = 135;
		else movedir = 180;
	
	}
	else
	{
		if (GetKeyPress(VK_A)) movedir = -90;
		else if (GetKeyPress(VK_D)) movedir = 90;
		else ismove = false;
	
	}
	Angle.y = movedir;
	
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

	if (ismove)
	{
		Position.x += speed * sindeg(Angle.y);
		Position.z += speed * cosdeg(Angle.y);

	}

	ItemList->Ishit(this);

}


void Player::UseWepon()
{
	//StrengtheningDataPlayer pdataOll;
	//StrengtheningDataPlayer* pdata;

	if (WeponNum == WeponMaxNum)
	{
		if (GetKeyTrigger(VK_LEFT))
			ChengeWeponNum = ((ChengeWeponNum + 1) % (WeponMaxNum - MainWeponNum)) + MainWeponNum;
		else if (GetKeyTrigger(VK_9))
		{
			delete wepon[ChengeWeponNum];
			wepon[ChengeWeponNum] = nullptr;

			for (int i = ChengeWeponNum; i < WeponMaxNum; i++)
				wepon[i] = wepon[i + 1];

			wepon[WeponMaxNum] = nullptr;
			WeponNum--;

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

	for (int i = MainWeponNum; i < WeponNum; i++)
	{
		wepon[i]->update();

	}


}

bool Player::CreateWepon(Weponid _id)
{
	if (WeponNum < WeponMaxNum)
	{
		initWepondata datInitWepon;
		datInitWepon.p = this;
		datInitWepon.pos = Position;
		datInitWepon.EnemyList = enemylist;
		datInitWepon.R = Resource;
		datInitWepon.pangle = 0;

		switch (_id)
		{
		case Wepon_missilelunther:
			waitWepon = new Wepon_MissileLunther(datInitWepon, myblist);
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

		wepon[WeponNum] = waitWepon;
		waitWepon = nullptr;
		WeponNum++;
		return true;

	}
	else return false;
	
}

void Player::CreateRelic()
{

	


}
