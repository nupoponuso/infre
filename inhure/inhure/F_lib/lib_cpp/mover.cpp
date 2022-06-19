//-------------------------------------------
//
// �v���[���[�A�e�A�G�̉��z�N���X 
//		auhor: fujioka tomoya
//		
//
//-------------------------------------------

//�C���N���[�h
#include "mover.h"
#include "Colision.h"
#include "ResourceManager.h"


namespace F_lib_Mover 
{
	//Mover�N���X-----------------------------------------

	// �R���X�g���N�^�FTask�N���X�R���X�g���N�^�̏��������X�g�t��
	//	�����o�ϐ��̏������@�����F�^�X�N���X�g,�������Wxy,�p�x,�X�s�[�h,�e�N�X�`���}�l�[�W���[
	Mover::Mover(F_lib_Fremworker::ResourceManager* _Resource, XMFLOAT3 _angle, float _speed)
		: Resource(_Resource), angle(_angle), speed(_speed), Alive(true), col(nullptr), hit(false)
	{
		Size = XMFLOAT3(1, 1, 1);

	}


	//getcol�֐�
	//�N���X�����o�̓����蔻��N���X
	Colision_2D * Mover::getcol()
	{
		if (col != nullptr)
		{
			Coldata_2D* dat = col->getColdata();
			dat->pos = XMFLOAT2(Position.x, Position.y);

		}

		return col;
	}


	//addhp�֐�
	//hp�ֈ����̉��Z
	void Mover::addhp(int _add)
	{
		if (hp >= 0) hp += _add;
	}

	//-----------------------------------------
	
	//mover�p��ʊ֐�
	
	float getLockAngle_2D(XMFLOAT2 _posthis, XMFLOAT2 _posterget)
	{
		float angle;
		XMFLOAT2 thispos = _posterget;
		thispos.x = thispos.x - _posthis.x;
		thispos.y = thispos.y - _posthis.y;
		angle = atan2(thispos.x, thispos.y)* 180.0f / 3.14f;

		return angle;
	}

	//getlockangle�֐�
	//���������̈ʒu������������̈ʒu�̊p�x���擾
	//XMFLOAT3 getlockangle_3D(Mover * _this, Mover * _terget)
	//{
	//	if (_terget == nullptr) 
	//		return XMFLOAT3();
	//
	//	return getlockangle_3D(_this->getcol()->box->Pos, _terget);
	//}
	//
	//
	////getlockangle�֐�
	////�������̈ʒu����������̈ʒu�̊p�x���擾
	//XMFLOAT3 getlockangle_3D(XMFLOAT3 _pos, Mover * _terget)
	//{
	//	XMFLOAT3 tergetpos, angle;
	//
	//	tergetpos = _terget->getcol()->box->Pos;
	//	tergetpos = XMFLOAT3(tergetpos.x - _pos.x, tergetpos.y - _pos.y, tergetpos.z - _pos.z);
	//
	//	angle.y = atan2(tergetpos.x, tergetpos.z);
	//	angle.x = atan2(tergetpos.y, hypot(tergetpos.z, tergetpos.x));
	//
	//	angle.y = angle.y * 180.0f / 3.14f;
	//	angle.x = angle.x * 180.0f / 3.14f;
	//	angle.z = 0;
	//
	//	return angle;
	//}
	//
	//-----------------------------------------
}
