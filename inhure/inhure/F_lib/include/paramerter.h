//-------------------------------------------
//
//		���L1d�f�[�^�N���X | paramerter.cpp |
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//player�I��enum
enum playerid
{
	playerid_1 = 0, 
	playerid_2,
	playerid_3,

	playerid_MAX
};


//�Q�[���f�[�^�p�\����
struct gemedate
{
	int playernum;

	gemedate()
	{
		playernum = playerid_1;

	}

};


//�@paramerter�N���X
//�@�N���X�����o
class paramerter
{
public:
	paramerter();

	void setdate();

	gemedate date;

};

