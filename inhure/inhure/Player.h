#pragma once

#include "Mover2D.h"
#include "MoverList.h"
#include "F_lib/include/Mesh_Fbxmodel.h"

#include "Wepon.h"

struct initplayerdata
{
	MoverList* bulletList, *enemyList,*enemybList,*itemList, *oList;
	F_lib_Fremworker::ResourceManager* R;

};

class Player:public Mover2D
{
public:
	Player(initplayerdata);

	void update();
	void Draw();

	void terhit(Mover2D*);
	void herhit(Mover2D*);

	F_lib_Mover::Colision_2D* getcol() override;

protected:
	void Move();
	void UseWepon();

	bool CreateWepon(enum weponId);
	void CreateRelic();

	class Wepon** wepon;
	class Wepon* waitWepon;
	std::vector<class Equipment*> relicList;
	F_lib_Render::Mesh_Fbx* mesh;
	MoverList* mybList, *ebList, *enemyList, *itemList,*oList;
	XMFLOAT3 cpos;

	//initWepondata datInitWepon;

	bool isMove;
	int hp, atack, defense, ep;
	int weponNum, weponMaxNum, speedRot, chengeWeponNum, mainWeponNum;
	float moveDir, moveDirOld;

};

