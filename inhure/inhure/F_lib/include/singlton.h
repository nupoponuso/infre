//-------------------------------------------
//
//　	　シングルトンクラス | Singleton.cpp |
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once


//　Singletonクラス
//　クラスメンバ
template <typename T>
class Singleton
{
public:
	static T* getins() { static T instance; return &instance; }
	
protected:
	Singleton() = default;				//外部インスタンス作成禁止
	virtual ~Singleton() = default;

private:
	Singleton(const Singleton& obj) = delete;				  //コピーコンストラクタ禁止
	Singleton(Singleton&&) = delete;				  //ムーブコンストラクタ禁止
	Singleton& operator = (const Singleton& obj) = delete;	  //代入演算子禁止
	Singleton& operator = (Singleton&&) = delete;	  //ムーブコンストラクタの代入禁止

};