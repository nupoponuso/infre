//#pragma once
//
//// インクルード
//#include <vector>
//#include <array>
//
//#include "comon.h"
//
//class WeaponFactory
//{
//public:
//	WeaponFactory();
//	~WeaponFactory();
//
//	HRESULT Create(int id);
//
//private:
//	class WeaponBase* Weapon;
//};
//
//
//class RelicFactory
//{
//public:
//	RelicFactory();
//	~RelicFactory();
//
//	HRESULT Create(int id);
//
//private:
//	class RelicBase* Reric;
//};
//
//class RandomFactory
//{
//public:
//	RandomFactory();
//	~RandomFactory();
//
//	HRESULT Create(int min, int max);
//
//public:
//	//std::uniform_int_distribution<> rand;
//private:
//
//};
//
//class Shop
//{
//public:
//	Shop();
//	~Shop();
//
//	void Open();
//	void Close();
//
//	void Update();
//	WeaponBase* GetWeapon(int no);
//
//private:
//	WeaponFactory* WeaponF;
//	RelicFactory* RelicF;
//	RandomFactory* RandF;
//	const float CoolTime;
//	float TimeCount;
//	std::array< class WeaponBase*, 10> WeaponArray;
//	std::array< class RelicBase*, 10 > RelicArray;
//};
//
