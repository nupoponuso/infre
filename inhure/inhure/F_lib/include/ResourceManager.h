//-------------------------------------------
//
//		ResourceManagerクラス | ResourceManager.cpp |
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once


//インクルード
#include "comon.h"
#include "EffekseerManeger.h"


namespace F_lib_Fremworker
{

	//　ResourceManagerクラス
	//　クラスメンバ
	class ResourceManager
	{
	public:
		ResourceManager();

		class MeshManeger* meshM;
		class TextureManeger* TM;
		F_lib_Render::EffekseerManeger* Em;

	};

}