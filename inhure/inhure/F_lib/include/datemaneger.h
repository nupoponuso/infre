//-------------------------------------------
//
// �@	�f�[�^���i�[����N���X 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


#pragma once

//�C���N���[�h
#include "comon.h"

namespace F_lib_Fremworker
{

	//�@datemaneger�N���X
	//�N���X�����o
	class dateManeger
	{
	public:
		dateManeger(ID3D11Device * _device, ID3D11DeviceContext *_deviceContext) : Device(_device), DeviceContext(_deviceContext) {}
		virtual void detaLode(int _deta) = 0;

	protected:
		ID3D11Device*			 Device;
		ID3D11DeviceContext*	 DeviceContext;

	};

}