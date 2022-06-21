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
//	std::random_device rnd;		// �񌈒�I�ȗ���������(�V�[�h�Ɏg�p)
//	std::mt19937 mt;			// �����Z���k�E�c�C�X�^��32�r�b�g��
//	mt.seed(rnd());				// �V�[�h�l�̎w��
//	std::uniform_int_distribution<> rand100(0, 99);	// [0, 99] �͈͂̈�l����
//
//	for (int i = 0; i < 20; i++) { 	// [0, 99]����20����
//		rand100(mt);
//
//	}
//
//	std::normal_distribution<> norm(50.0, 10.0);       // ����50, ���U�l10�̐��K���z
//	for (int i = 0; i < 20; ++i) {
//		norm(mt);
//	}
//}
//
//RandomFactory::~RandomFactory()
//{
//}
