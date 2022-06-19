//-------------------------------------------
//
// �v���[���[�A�e�A�G�̉��z�N���X 
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//�C���N���[�h
#include "comon.h"
#include "ResourceManager.h"
#include "Colision.h"


namespace F_lib_Mover
{

	//�@Mover�N���X 
	//	�N���X�����o
	class MoverBase
	{
	public:
		//�R���X�g���N�^
		MoverBase(F_lib_Fremworker::ResourceManager*); //���W�A�p�x�Ȃǂ̏�����

		//�����o�֐�
		virtual void update() = 0;
		virtual void Draw() = 0;
		
		//�Q�b�^�[
		XMFLOAT3  getPosition() { return Position; }
		XMFLOAT3  getSize() { return Size; }
		XMFLOAT3  getAngle() { return Angle; }

		bool	 Alive;			//��������

	protected:
		//�����o�ϐ�
		F_lib_Fremworker::ResourceManager* Resource;

		XMFLOAT3 Position;		//���W
		XMFLOAT3 Size;			//�T�C�Y
		XMFLOAT3 Angle;			//�p�x

		bool hit;

	};

	//-----------------------------------------

	//mover�p��ʊ֐�
	float getLockAngle_2D(XMFLOAT2 _posthis, XMFLOAT2 _posterget);

}



//getlockangle�֐��@
//����������������̊p�x���擾�@�����F�@����l,�^�[�Q�b�g
//XMFLOAT3 getlockangle(Mover* _this,Mover* _terget);

//getlockangle�֐��@
//����������������̊p�x���擾�@�����F�@�ʒu,�^�[�Q�b�g
//XMFLOAT3 getlockangle(XMFLOAT3 _pos, Mover* _terget);
