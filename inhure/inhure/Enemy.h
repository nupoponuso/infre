

#pragma once

//�C���N���[�h
#include "Mover2D.h"
#include "MoverList.h"
#include "F_lib/include/Mesh_Fbxmodel.h"


//�G�̏������\����
struct initenemydata
{
	F_lib_Fremworker::ResourceManager * R;
	MoverList* bulletlist,*mylist;
	class Player* p;
	class ItemFactory* itemfactory;
	XMFLOAT3 pos;
	float speed;

};


//�@Enemy�N���X�@�p��->Mover2D
//�@�G�̊��N���X
class Enemy:public Mover2D
{
public:
	Enemy(initenemydata);
	~Enemy();

	virtual void Update();
	void Draw();
	void terhit(Mover2D*);
	void herhit(Mover2D*);

	F_lib_Mover::Colision_2D* getcol();

	class Player* getPlayer() { return p; }
	int getHp()		 { return hp; }
	int getDefence() { return defense; }

	void addHp(int _add) { hp += _add; }

protected:
	virtual void move()=0;
	virtual void myAtack()=0;

	class Player* p;
	class ItemFactory* itemfactory;
	F_lib_Render::Mesh_Fbx* mesh;
	F_lib_Mover::Colision_2D* atackCol;
	MoverList* bulletList,* myList;
	int hp, atack, defense, ep;
	float speed;
	bool isAtack, ismove;;

};

