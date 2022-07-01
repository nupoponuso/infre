
#pragma once


struct StrengtheningDataPlayer
{
	//float speed;
	int hp, atack, defense, ep;//�����l�@���ۂɎg�p����Ƃ��ɂ́@�ϐ��̒l�~0.01f�Ƃ������ƂɂȂ�

	StrengtheningDataPlayer()
	{
		hp = atack = defense = ep = 0;
	}

};


struct StrengtheningDataWepon
{
	int atack;
	float lockOn;

};


class Equipment
{
public:
	Equipment() :dataP(nullptr), dataW(nullptr) {}

	virtual void update() = 0;
	
	StrengtheningDataPlayer* getdataP() { return dataP; }
	StrengtheningDataWepon*  getdataW() { return dataW; }

protected:

	StrengtheningDataPlayer* dataP;
	StrengtheningDataWepon*  dataW;


};

