
#pragma once

struct StrengtheningDataPlayer
{

};


struct StrengtheningDataWepon
{

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

