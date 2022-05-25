//-------------------------------------------
//
// �e�N�X�`���Ǘ��N���X | TextureManeger.cpp |
//		auhor: hujioka tomoya
//
//		
//-------------------------------------------

#pragma once


//�C���N���[�h
#include "comon.h"
#include <vector>

namespace F_lib_Fremworker
{
	// TextureManeger�N���X
	// �N���X�����o
	class TextureManeger
	{
	public:
		TextureManeger(ID3D11Device* _deice);
		~TextureManeger();

		virtual HRESULT loadTex() =0;	//�e�N�X�`���̃��[�h

		//�Q�b�^�[
		ID3D11ShaderResourceView* gettex(int _id) { return list[_id]; }

	protected:

		ID3D11Device*			  Device;
		std::vector<ID3D11ShaderResourceView*> list;
		HRESULT hr;

	};

}