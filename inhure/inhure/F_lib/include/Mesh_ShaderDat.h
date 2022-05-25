#pragma once

#include "comon.h"

namespace F_lib_Render
{
	class Mesh_ShaderDat
	{
	public:
		Mesh_ShaderDat();

		ID3D11VertexShader* getVertexShader() { return VertexShader; }
		ID3D11PixelShader*  getPixelShader() { return PixelShader; }
		ID3D11InputLayout*  getVertexLayout() { return VertexLayout; }

	protected:
		HRESULT MakeShader(LPCWSTR, LPCSTR, LPCSTR, void**, ID3DBlob**, ID3D11Device*);
		void MakeVertexLayout(ID3DBlob*, const D3D11_INPUT_ELEMENT_DESC*, ID3D11Device*);

		ID3D11VertexShader*	 VertexShader;
		ID3D11PixelShader*	 PixelShader;
		ID3D11InputLayout*	 VertexLayout;

	};

	class Mesh_ShaderDat3D :public Mesh_ShaderDat
	{
	public:
		Mesh_ShaderDat3D(LPCWSTR, bool,ID3D11Device*);
	private:
		void MakeVertexLayout(ID3DBlob *, bool, ID3D11Device*);
	};

	class Mesh_ShaderDat2D :public Mesh_ShaderDat
	{
	public:
		Mesh_ShaderDat2D(LPCWSTR, ID3D11Device*);

	private:
		void MakeVertexLayout(ID3DBlob *, ID3D11Device*);
	};
}