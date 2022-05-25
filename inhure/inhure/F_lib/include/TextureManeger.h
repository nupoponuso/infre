//-------------------------------------------
//
// テクスチャ管理クラス | TextureManeger.cpp |
//		auhor: hujioka tomoya
//
//		
//-------------------------------------------

#pragma once


//インクルード
#include "comon.h"
#include <vector>

namespace F_lib_Fremworker
{
	// TextureManegerクラス
	// クラスメンバ
	class TextureManeger
	{
	public:
		TextureManeger(ID3D11Device* _deice);
		~TextureManeger();

		virtual HRESULT loadTex() =0;	//テクスチャのロード

		//ゲッター
		ID3D11ShaderResourceView* gettex(int _id) { return list[_id]; }

	protected:

		ID3D11Device*			  Device;
		std::vector<ID3D11ShaderResourceView*> list;
		HRESULT hr;

	};

}