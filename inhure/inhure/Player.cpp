#include "Player.h"

#include "F_lib/include/Mesh_Sprite.h"
#include "RM.h"
#include "MeshM.h"
#include "input.h"

#include "Wepon_MissileLunther.h"
#include "WeponSword.h"
#include "WeponBoomerang.h"
#include "WeponFlamethrower.h"
#include "WeponLyzer.h"

#include "Equipment1.h"

#include "item.h"


using namespace F_lib_Mover;
using namespace F_lib_Render;

Player::Player(initplayerdata _dat)
	:Mover2D(_dat.R), enemyList(_dat.enemyList), mybList(_dat.bulletList), ebList(_dat.enemybList), itemList(_dat.itemList), oList(_dat.oList)
{
	Position = XMFLOAT3();
	mesh = _dat.R->meshM->getModel(0);

	speed = 1.25f;
	speedRot = 10;//方向制御の時
	//rotspeed = 4;//旋回制御の時
	wepon.weponNum = 0;
	isLevelUp = false;
	baseStetas.hpMax =  stetas.hp = stetas.hpMax = 1000;
	stetas.epMax = 100;
	stetas.ep = 0;
	baseStetas.defense = stetas.defense = 0;
	stetas.level = 1;
	atack = 0;

	col = new Colision_2D(Colision_2D::Col_crecle);
	col->getColdata()->size.x = 1;
	
	cPos = Position;
	cPos.y += 150;
	Resource->meshM->getCamera()->setPosition(cPos);
	Resource->meshM->getCamera()->update();
	
	//継承したときにここのパラメータ設定などを派生クラスに映す
	wepon.weponMaxNum = 6;
	wepon.wepon = new Wepon*[wepon.weponMaxNum];

	wepon.chengeWeponNum = wepon.mainWeponNum = 2;
	CreateWepon(weponId::Wepon_boomerang);
	CreateWepon(weponId::Wepon_flamethrower);

}

void Player::Update()
{
	levelManagement();
	Move();
	UseWepon();

	cPos = Position;
	cPos.y += 80;

}

void Player::Draw()
{
	Resource->meshM->getCamera()->setPosition(cPos);
	Resource->meshM->getCamera()->update();

	mesh->setPosition(Position);
	mesh->setangle(Angle);
	mesh->setSize(0.01f);
	mesh->RDraw();

	for (int i = 0; i < wepon.weponNum; i++)
		wepon.wepon[i]->Draw();

}

void Player::terhit(Mover2D *_m)
{
	switch (_m->getMyid())
	{
	case mover_enemy:

		break;
	case mover_bullet:

		break;
	case mover_item:
	{
		Item* item = dynamic_cast<Item*>(_m);
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
	}
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
	
	//方向制御
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
	//旋回制御
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
	if (GetKeyTrigger(VK_0))
		CreateRelic();

	for (auto relic : relicList)
		relic->update();
	
	if (wepon.weponNum == wepon.weponMaxNum)
	{
		if (GetKeyTrigger(VK_LEFT))
			wepon.chengeWeponNum = ((wepon.chengeWeponNum + 1) % (wepon.weponMaxNum - wepon.mainWeponNum)) + wepon.mainWeponNum;
		else if (GetKeyTrigger(VK_9))
		{
			delete wepon.wepon[wepon.chengeWeponNum];

			for (int i = wepon.chengeWeponNum; i < wepon.weponMaxNum; i++)
				wepon.wepon[i] = wepon.wepon[i + 1];

			wepon.wepon[wepon.weponMaxNum] = nullptr;
			wepon.weponNum--;

		}

	}
	//else if (GetKeyTrigger(VK_0))
	//{
	//	CreateWepon(Weponid::Wepon_missilelunther);
	//}

	for (int i = 0; i < wepon.weponNum; i++)
		wepon.wepon[i]->Update();

}

void Player::levelManagement()
{
	if (!isLevelUp)
	{
		if (stetas.ep > stetas.epMax)
		{
			isLevelUp = true;
			stetas.ep -= stetas.epMax;
			stetas.level++;

		}

	}

	if (isLevelUp)//ここでレベルアップ時のパラメータアップを行う継承時ここは派生クラスで書く
	{
		if (stetas.level < 30) 
		{
			isLevelUp = false;

			speed += 0.02;
			stetas.epMax += 50;
			//baseStetas.hpMax += 50;

		}

	}

}

void Player::StetasManegement()
{
	//pdataOll
	stetas.hpMax = baseStetas.hpMax + (baseStetas.hpMax * float(0.01f*pdataOll.hp));
	stetas.defense = baseStetas.defense + (baseStetas.defense * float(0.01f*pdataOll.defense));


}

bool Player::CreateWepon(weponId _id)
{
	if (wepon.weponNum < wepon.weponMaxNum)
	{
		Wepon* waitWepon = nullptr;;
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
		//case Wepon_lyzer:
			waitWepon = new WeponLyzer(datInitWepon);
			break;
		case Wepon_flamethrower:
			waitWepon = new WeponFlamethrower(datInitWepon, mybList);
			break;
		case Wepon_showd:
			waitWepon = new WeponSword(datInitWepon);
			break;
		case Wepon_boomerang:
			waitWepon = new WeponBoomerang(datInitWepon);

			break;
		}

		wepon.wepon[wepon.weponNum] = waitWepon;
		wepon.weponNum++;
		return true;

	}
	else return false;
	
}

void Player::CreateRelic()
{
	StrengtheningDataPlayer* pdata;

	pdataOll.atack = pdataOll.hp = pdataOll.ep = pdataOll.defense = 0;
	relicList.push_back(new Equipment1());

	for (auto relic : relicList)
	{
		if (relic->getdataP() != nullptr)
		{
			pdata = relic->getdataP();
			pdataOll.atack += pdata->atack;
			pdataOll.hp += pdata->hp;
			pdataOll.ep += pdata->ep;
			pdataOll.defense += pdata->defense;

		}

	}

	StetasManegement();

}
