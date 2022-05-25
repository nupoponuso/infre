//-------------------------------------------
//
// �v���[���[�A�e�A�G�̉��z�N���X 
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//�C���N���[�h
#include "comon.h"
#include "Mesh_Sprite.h"
#include "ResourceManager.h"
#include "Colision.h"
//#include "moverManeger.h"

//	�\����
//	�e�N�X�`���A�j���[�V�����p�\����
//typedef struct
//{
//	int nPatNo;
//	int nCount;
//}ANIM_PAT;


//�ړ������penum
enum mover_id
{
	mover_player = 0,
	mover_bullet,
	mover_enemy,
	mover_Obstacle,

	mover_max
};



namespace F_lib_Mover
{

	//�@Mover�N���X 
	//	�N���X�����o
	class Mover
	{
	public:
		//�R���X�g���N�^
		Mover(F_lib_Fremworker::ResourceManager*, XMFLOAT3 _angle, float _speed); //���W�A�p�x�Ȃǂ̏�����

		//�����o�֐�
		virtual void update() = 0;
		virtual void Draw() = 0;
		virtual void terhit(Mover*) = 0;
		virtual void herhit(Mover*) = 0;

		void addhp(int _add);

		void sethit(bool _f = false, int _count = 0) { hit = _f; hitcount = _count; }

		//�Q�b�^�[
		XMFLOAT3  getthisposition() { return Position; }
		XMFLOAT3  getthisSize() { return Size; }
		XMFLOAT3  getangle() { return angle; }
		virtual F_lib_Mover::Colision_2D* getcol();

		mover_id getmyid() { return myid; }
		int  gethp()	   { return hp; }
		int  getmaxhp()    { return Maxhp; }
		int  getatack()    { return atack; }
		bool gethit()      { return hit; }

		bool	 Alive;			//��������

	protected:
		//�����o�ϐ�
		F_lib_Fremworker::ResourceManager* Resource;
		F_lib_Mover::Colision_2D* col;
	
		mover_id myid;

		XMFLOAT3 Position;		//���W
		XMFLOAT3 Size;			//�T�C�Y
		XMFLOAT3 angle;			//�p�x
		float	 speed;			//�X�s�[�h

		int hp, Maxhp, atack, hitcount;
		bool hit;

	};

}

//-----------------------------------------

//mover�p��ʊ֐�

//getlockangle�֐��@
//����������������̊p�x���擾�@�����F�@����l,�^�[�Q�b�g
//XMFLOAT3 getlockangle(Mover* _this,Mover* _terget);

//getlockangle�֐��@
//����������������̊p�x���擾�@�����F�@�ʒu,�^�[�Q�b�g
//XMFLOAT3 getlockangle(XMFLOAT3 _pos, Mover* _terget);
