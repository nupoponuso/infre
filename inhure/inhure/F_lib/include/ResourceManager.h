//-------------------------------------------
//
//		ResourceManager�N���X | ResourceManager.cpp |
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once


//�C���N���[�h
#include "comon.h"
#include "EffekseerManeger.h"


namespace F_lib_Fremworker
{

	//�@ResourceManager�N���X
	//�@�N���X�����o
	class ResourceManager
	{
	public:
		ResourceManager();

		class MeshManeger* meshM;
		class TextureManeger* TM;
		F_lib_Render::EffekseerManeger* Em;

	};

}