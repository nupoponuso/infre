

#pragma once


//�C���N���[�h
#include "Mover2D.h"
#include "MoverList.h"
#include "Mesh_Fbxmodel.h"


//�\����

//
struct InitBossData
{
	F_lib_Fremworker::ResourceManager* R;
	XMFLOAT3 Pos;

};

//
struct BossStetase
{
	int hp;

};


//�{�X�̊��N���X
class Boss : public Mover2D
{
public:
	Boss(InitBossData);

	void Update();
	void Draw();
	void terhit(Mover2D*);
	void herhit(Mover2D*);

	F_lib_Mover::Colision_2D* getcol();

	void addHp(int _add) { stetas.hp += _add; }

protected:
	MoverList* pbList;
	BossStetase stetas;
	F_lib_Render::Mesh_Fbx* mesh;

};

