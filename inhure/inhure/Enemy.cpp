

//�C���N���[�h
#include "Enemy.h"

#include "RM.h"
#include "F_lib/include/mover.h"
//#include "Bullet.h"
#include "Player.h"
#include <random>
#include "ItemFactory.h"


//���O��ԃX�R�[�v����
using namespace F_lib_Mover;
using namespace F_lib_Render;


//�R���X�g���N�^
//������
Enemy::Enemy(initenemydata _dat) : Mover2D(_dat.R), bulletList(_dat.bulletlist), p(_dat.p),itemfactory(_dat.itemfactory)
{
	ep = 0;
	
	speed = _dat.speed;
	Myid = mover_enemy;
	myList = _dat.mylist;
	col = new Colision_2D(Colision_2D::Col_crecle);
	col->getColdata()->size.x = 1;

	Position = _dat.pos;
	mesh = _dat.R->meshM->getModel(2);

}


//�f�X�g���N�^
//���񂾂Ƃ�
Enemy::~Enemy()
{
	p->addEp(ep);

	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rand(0, 10);
	
	int i = rand(mt);

	if (i == 0)
		itemfactory->Create(Position);

}


//Update�֐�
//�G�̑S�̓I�ȍs��
void Enemy::Update()
{
	if (hp < 0)
		Alive = false;

	move();
	myAtack();

	if (myList->getlistNum() > 0)
		myList->Ishit(this);
}


//�@Draw�֐�
//�@�`�揈��
void Enemy::Draw()
{
	mesh->setangle(Angle);
	mesh->setPosition(Position);
	mesh->RDraw();

}


//terhit�֐�
//�\���I�q�b�g�C�x���g
void Enemy::terhit(Mover2D * _m)
{

	switch (_m->getMyid())
	{
	
	case mover_enemy:
		
		float len, angle;
		len = col->getColdata()->size.x*0.9f;
		
		angle = F_lib_Mover::getLockAngle_2D(XMFLOAT2(this->getPosition().x, this->getPosition().y), XMFLOAT2(_m->getPosition().x, _m->getPosition().y));

		Position.x += len * sindeg(-angle);
		Position.z += len * cosdeg(-angle);

		break;
	}
}


//herhit�֐�
//�󓮓I�q�b�g�C�x���g
void Enemy::herhit(Mover2D *_m)
{
	switch (_m->getMyid())
	{
	case mover_bullet:
	
		break;

	case mover_enemy:

		float len, angle;
		len = col->getColdata()->size.x*0.1f;
		angle = F_lib_Mover::getLockAngle_2D(XMFLOAT2(this->getPosition().x, this->getPosition().z), XMFLOAT2(_m->getPosition().x, _m->getPosition().z));

		Position.x += len * sindeg(-angle);
		Position.z += len * cosdeg(-angle);
		break;
	}
	 
}


//getcol�֐�
//�����蔻��̎擾
F_lib_Mover::Colision_2D * Enemy::getcol()
{
	col->getColdata()->pos = XMFLOAT2(Position.x, Position.z);
	
	return col;

}
