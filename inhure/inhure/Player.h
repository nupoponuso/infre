#pragma once

#include "Mover2D.h"
#include "MoverList.h"
#include "F_lib/include/Mesh_Fbxmodel.h"

#include "Wepon.h"
#include "Equipment.h"

struct initplayerdata
{
	MoverList* bulletList, *enemyList,*enemybList,*itemList, *oList;
	F_lib_Fremworker::ResourceManager* R;

};

struct PlayerStetasData
{
	int hp, hpMax, defense, ep, epMax, level;

};

struct PlayerStetasDataBase
{
	int hpMax, defense;

};

struct PlayerWeponData
{
	class Wepon** wepon;
	int weponNum, weponMaxNum, chengeWeponNum, mainWeponNum;
};

class Player:public Mover2D
{
public:
	Player(initplayerdata);

	void Update();
	void Draw();

	void terhit(Mover2D*);
	void herhit(Mover2D*);

	F_lib_Mover::Colision_2D* getcol() override;

	int getAtack()      { return atack; }
	bool getIsLevelUp() { return isLevelUp; }
	PlayerStetasData &getStetas() { return stetas; }

	void addHp(int _add) { stetas.hp += _add; }
	void addEp(int _add) { stetas.ep += _add; }

protected:

	void Move();
	void UseWepon();
	void levelManagement();
	void StetasManegement();

	bool CreateWepon(enum weponId);
	void CreateRelic();

	std::vector<class Equipment*> relicList;
	F_lib_Render::Mesh_Fbx* mesh;
	MoverList* mybList, *ebList, *enemyList, *itemList,*oList;
	XMFLOAT3 cPos;

	bool isMove,isLevelUp;
	PlayerStetasData stetas;
	PlayerWeponData wepon;
	PlayerStetasDataBase baseStetas;
	StrengtheningDataPlayer pdataOll;
	int speedRot;
	float moveDir;

};

