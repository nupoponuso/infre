
#pragma once


struct StrengtheningDataPlayer
{
	//float speed;
	int hp, atack, defense, ep;//強化値　実際に使用するときには　変数の値×0.01fということになる

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

