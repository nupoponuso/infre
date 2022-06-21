//#include "Shop.h"
//
//#include <random>
//
//#include "Text.h"
//
//Shop::Shop()
//	: WeaponF(nullptr)
//	, RelicF(nullptr)
//	, RandF(nullptr)
//	, CoolTime(300.0f)
//	, TimeCount(0.0f)
//{
//	WeaponF = new WeaponFactory();
//	RelicF = new RelicFactory();
//	RandF = new RandomFactory();
//	RandF->Create(0, 99);
//}
//
//Shop::~Shop()
//{
//	delete WeaponF;
//	delete RelicF;
//	delete RandF;
//}
//
//void Shop::Open()
//{
//	WeaponF->Create(5);
//}
//
//void Shop::Close()
//{
//}
//
//void Shop::Update()
//{
//}
//
//RandomFactory::RandomFactory()
//{
//	std::random_device rnd;		// 非決定的な乱数生成器(シードに使用)
//	std::mt19937 mt;			// メルセンヌ・ツイスタの32ビット版
//	mt.seed(rnd());				// シード値の指定
//	std::uniform_int_distribution<> rand100(0, 99);	// [0, 99] 範囲の一様乱数
//
//	for (int i = 0; i < 20; i++) { 	// [0, 99]から20個生成
//		rand100(mt);
//
//	}
//
//	std::normal_distribution<> norm(50.0, 10.0);       // 平均50, 分散値10の正規分布
//	for (int i = 0; i < 20; ++i) {
//		norm(mt);
//	}
//}
//
//RandomFactory::~RandomFactory()
//{
//}
