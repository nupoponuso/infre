
#pragma once


struct StrengtheningDataPlayer
{
	float hp,speed;
	int atack, defense, ep;

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

