//-------------------------------------------
//
//		�r���{�[�h�N���X �@| Mesh_billbord.cpp |
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//�C���N���[�h
#include "Mesh_Sprite.h"

namespace F_lib_Render
{

	//Mesh_billbord�N���X�@�p��->Mesh_Sprite
	//�N���X�����o

	class Mesh_billbord : public Mesh_Sprite
	{
	public:
		Mesh_billbord(ID3D11Device * _Device, ID3D11DeviceContext * _DeviceContext, class Camera_3D* _Camera);

		void Draw() override;
		void RDraw();

		void setPosition(XMFLOAT3 _Pos) { Position = _Pos; }

	};

}