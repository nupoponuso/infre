

//インクルード
#include "Mesh_ShaderDat.h"
#include "comon.h"

namespace F_lib_Render
{
	//シェーダファイルからシェーダの取り出し
	Mesh_ShaderDat::Mesh_ShaderDat()
	{}


	//
	HRESULT Mesh_ShaderDat::MakeShader(LPCWSTR _FileName, LPCSTR _FuncName, LPCSTR _ProfileName, void** _Shader, ID3DBlob** _Blob, ID3D11Device*Device)
	{
	
		ID3DBlob *pErrors = NULL;
		if (FAILED(D3DCompileFromFile(_FileName, NULL, NULL, _FuncName, _ProfileName, NULL, 0, _Blob, &pErrors)))
		{
			char*p = (char*)pErrors->GetBufferPointer();
			MessageBoxA(0, p, 0, MB_OK);
			return E_FAIL;
		}

		SAFE_RELEASE(pErrors);

		char szProfile[3] = { 0 };
		memcpy(szProfile, _ProfileName, 2);

		if (strcmp(szProfile, "vs") == 0)//Vertex Shader
		{
			if (FAILED(Device->CreateVertexShader((*_Blob)->GetBufferPointer(), (*_Blob)->GetBufferSize(), NULL, (ID3D11VertexShader**)_Shader))) return E_FAIL;
		}
		if (strcmp(szProfile, "ps") == 0)//Pixel Shader
		{
			if (FAILED(Device->CreatePixelShader((*_Blob)->GetBufferPointer(), (*_Blob)->GetBufferSize(), NULL, (ID3D11PixelShader**)_Shader))) return E_FAIL;
		}
		if (strcmp(szProfile, "gs") == 0)//Geometry Shader
		{
			if (FAILED(Device->CreateGeometryShader((*_Blob)->GetBufferPointer(), (*_Blob)->GetBufferSize(), NULL, (ID3D11GeometryShader**)_Shader))) return E_FAIL;
		}
		if (strcmp(szProfile, "hs") == 0)//Hull Shader
		{
			if (FAILED(Device->CreateHullShader((*_Blob)->GetBufferPointer(), (*_Blob)->GetBufferSize(), NULL, (ID3D11HullShader**)_Shader))) return E_FAIL;
		}
		if (strcmp(szProfile, "ds") == 0)//Domain Shader
		{
			if (FAILED(Device->CreateDomainShader((*_Blob)->GetBufferPointer(), (*_Blob)->GetBufferSize(), NULL, (ID3D11DomainShader**)_Shader))) return E_FAIL;
		}
		if (strcmp(szProfile, "cs") == 0)//Compute Shader
		{
			if (FAILED(Device->CreateComputeShader((*_Blob)->GetBufferPointer(), (*_Blob)->GetBufferSize(), NULL, (ID3D11ComputeShader**)_Shader))) return E_FAIL;
		}
		return S_OK;

	}


	//
	void Mesh_ShaderDat::MakeVertexLayout(ID3DBlob *pCompiledShader, const D3D11_INPUT_ELEMENT_DESC* layout, ID3D11Device*Device)
	{
		UINT numElements = sizeof(layout) / sizeof(layout[0]);

		//頂点インプットレイアウトを作成
		Device->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &VertexLayout);

	}


	//
	Mesh_ShaderDat3D::Mesh_ShaderDat3D(LPCWSTR _FileName, bool _useSkin, ID3D11Device* Device)
	{
		ID3DBlob *_Blob = NULL;
		if(!_useSkin) MakeShader(_FileName, "VS", "vs_5_0", (void**)&VertexShader, &_Blob, Device);	//バーテックスシェーダー作成
		else MakeShader(_FileName, "VS_SKIN", "vs_5_0", (void**)&VertexShader, &_Blob, Device);	//バーテックスシェーダー作成
		MakeVertexLayout(_Blob, _useSkin, Device);
		MakeShader(_FileName, "PS", "ps_5_0", (void**)&PixelShader, &_Blob, Device);		//ピクセルシェーダー作成

	}


	//
	void Mesh_ShaderDat3D::MakeVertexLayout(ID3DBlob *pCompiledShader, bool _useSkin, ID3D11Device* Device)
	{
		
		UINT numElements;

		if (_useSkin)
		{
			//頂点インプットレイアウトを定義	
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION"   , 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,							 D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "NORMAL"     , 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "TEXCOORD"   , 0, DXGI_FORMAT_R32G32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "BONEINDEX"  , 0, DXGI_FORMAT_R32G32B32A32_UINT,  0 ,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "BONEWEIGHT" , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0 ,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},

			};

			Mesh_ShaderDat::MakeVertexLayout(pCompiledShader, layout, Device);
			numElements = sizeof(layout) / sizeof(layout[0]);

			//頂点インプットレイアウトを作成
			Device->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &VertexLayout);

		}
		else {
			//頂点インプットレイアウトを定義	
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{"POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,							   D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

			};

			//Mesh_ShaderDat::MakeVertexLayout(pCompiledShader, layout);
			numElements = sizeof(layout) / sizeof(layout[0]);

			//頂点インプットレイアウトを作成
			Device->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &VertexLayout);

		}

	}


	//
	Mesh_ShaderDat2D::Mesh_ShaderDat2D(LPCWSTR _FileName, ID3D11Device* Device)
	{
		ID3DBlob *_Blob = NULL;
		MakeShader(_FileName, "VS", "vs_5_0", (void**)&VertexShader, &_Blob, Device);
		MakeVertexLayout(_Blob, Device);
		MakeShader(_FileName, "PS", "ps_5_0", (void**)&PixelShader, &_Blob, Device);

	}


	//
	void Mesh_ShaderDat2D::MakeVertexLayout(ID3DBlob * pCompiledShader, ID3D11Device*_Device)
	{
		//頂点インプットレイアウトを定義	
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		UINT numElements = sizeof(layout) / sizeof(layout[0]);

		//頂点インプットレイアウトを作成
		_Device->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &VertexLayout);
		//Mesh_ShaderDat::MakeVertexLayout(pCompiledShader, layout);

	}
}