//-------------------------------------------
//
//		描画用の仮想クラス | Mesh.cpp |
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//インクルード
#include "comon.h"
#include "Camera.h"
#include "Mesh_ShaderDat.h"


namespace F_lib_Render
{

	//　Meshクラス　
	//　クラスメンバ
	class Mesh
	{
	public:
		Mesh(ID3D11Device* _Device, ID3D11DeviceContext* _DeviceContext, Camera* _Camera);

		virtual void	Draw() = 0;

		void setPosition(XMFLOAT3 Pos) { Position = Pos; }
		void setSize(XMFLOAT3 Siz) { Size = Siz; }
		void setSize(float Siz) { Size = XMFLOAT3(Siz, Siz, Siz); }
		void setangle(XMFLOAT3 ang) { angle = ang; }
		void setCamera(Camera* _C) { camera = _C; }
		void setShader(Mesh_ShaderDat* _Shader) { Shader = _Shader; }

		XMFLOAT3 getPosition() { return Position; }
		XMFLOAT3 getsize() { return Size; }
		XMFLOAT3 getangle() { return angle; }

		Camera* getcamera() { return camera; }
		Mesh_ShaderDat* getShader() { return Shader; };

	protected:
		virtual HRESULT InitConstantBuffer() = 0;

		ID3D11Device*		 Device;
		ID3D11DeviceContext* DeviceContext;

		ID3D11SamplerState*  SamplerState;

		ID3D11Buffer*		 ConstantBuffer;
		ID3D11Buffer*		 VertexBuffer;

		Mesh_ShaderDat* Shader;
		Camera* camera;

		XMFLOAT3 Position, Size, angle;

	};

}