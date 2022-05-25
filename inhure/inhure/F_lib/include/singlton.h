//-------------------------------------------
//
//�@	�@�V���O���g���N���X | Singleton.cpp |
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once


//�@Singleton�N���X
//�@�N���X�����o
template <typename T>
class Singleton
{
public:
	static T* getins() { static T instance; return &instance; }
	
protected:
	Singleton() = default;				//�O���C���X�^���X�쐬�֎~
	virtual ~Singleton() = default;

private:
	Singleton(const Singleton& obj) = delete;				  //�R�s�[�R���X�g���N�^�֎~
	Singleton(Singleton&&) = delete;				  //���[�u�R���X�g���N�^�֎~
	Singleton& operator = (const Singleton& obj) = delete;	  //������Z�q�֎~
	Singleton& operator = (Singleton&&) = delete;	  //���[�u�R���X�g���N�^�̑���֎~

};