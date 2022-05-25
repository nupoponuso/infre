//-------------------------------------------
//
//		共有1dデータクラス | paramerter.cpp |
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//player選択enum
enum playerid
{
	playerid_1 = 0, 
	playerid_2,
	playerid_3,

	playerid_MAX
};


//ゲームデータ用構造体
struct gemedate
{
	int playernum;

	gemedate()
	{
		playernum = playerid_1;

	}

};


//　paramerterクラス
//　クラスメンバ
class paramerter
{
public:
	paramerter();

	void setdate();

	gemedate date;

};

