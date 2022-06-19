//-------------------------------------------
//
// �@Effekseer�Ǘ��N���X�N���X | EffekseerManeger.cpp |
//		auhor: hujioka tomoya
//
//		12/18�����܂���
//-------------------------------------------

#pragma once

//�C���N���[�h
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <vector>
#include "comon.h"



//���C�u�����̃��[�h
#ifdef _DEBUG
#pragma comment(lib, "EffekseerD.lib")
#pragma comment(lib, "EffekseerRendererDX11D.lib")
#else
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX11.lib")
#endif


namespace F_lib_Render
{
	//EffekseerManeger�N���X
	//�N���X�����o
	class EffekseerManeger
	{
	public:
		EffekseerManeger(ID3D11Device*, ID3D11DeviceContext*,class Camera_3D*);

		void update();
		void Draw();

		//�����F�G�t�F�N�gid,�ʒu,�p�x,�T�C�Y
		Effekseer::Handle play(int, XMFLOAT3);

		//�����F�G�t�F�N�gid,�ʒu,�p�x,�T�C�Y
		Effekseer::Handle play(int, XMFLOAT3, XMFLOAT3, XMFLOAT3);
		//�����F�G�t�F�N�gid,�ʒu,�p�x,�T�C�Y
		Effekseer::Handle play(int, XMFLOAT3, XMFLOAT3, float);

		void setstop(Effekseer::Handle);

		void setposition(Effekseer::Handle, XMFLOAT3);
		void setangle(Effekseer::Handle, XMFLOAT3);
		void setScale(Effekseer::Handle, XMFLOAT3);
		void setScale(Effekseer::Handle, float);

		void setColor(Effekseer::Handle, XMFLOAT3);
		void setColor(Effekseer::Handle, XMFLOAT4);

		void setdate(Effekseer::Handle, XMFLOAT3, XMFLOAT3, XMFLOAT3);

		bool getinstance(Effekseer::Handle);


	private:
		class Camera_3D* camera;

		EffekseerRendererDX11::RendererRef rendarer;
		Effekseer::ManagerRef manager;
		std::vector<Effekseer::EffectRef>  effect;
		
		int time = 0;
	};

}