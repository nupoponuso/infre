//-------------------------------------------
//
//		2Dスプライトクラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//インクルード
#include "Mesh_Sprite.h"
#include "RenderingEngine.h"


namespace F_lib_Render
{

	//コンストラクタ
	//初期化
	Mesh_Sprite::Mesh_Sprite(ID3D11Device * _Device, ID3D11DeviceContext * _DeviceContext, Camera* _Camera) : Mesh(_Device, _DeviceContext, _Camera)
	{
		texureUV = XMFLOAT2(0.0, 0.0);
		textureFream = XMFLOAT2(1, 1);
		Position.z = 0;
		Color = XMFLOAT4(1, 1, 1, 1);
		angle = XMFLOAT3();

	}


	//　InitModel関数
	//　モデルの初期化
	HRESULT Mesh_Sprite::InitModel()
	{
		Vertex_2D vertices[4];

		vertices[0].Pos = XMFLOAT3(0.5f, 0.5f, 0.0f);
		vertices[1].Pos = XMFLOAT3(0.5f, -0.5f, 0.0f);
		vertices[2].Pos = XMFLOAT3(-0.5f, 0.5f, 0.0f);
		vertices[3].Pos = XMFLOAT3(-0.5f, -0.5f, 0.0f);

		vertices[0].TexUV = XMFLOAT2(1, 0);
		vertices[1].TexUV = XMFLOAT2(1, 1);
		vertices[2].TexUV = XMFLOAT2(0, 0);
		vertices[3].TexUV = XMFLOAT2(0, 1);

		D3D11_BUFFER_DESC bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vertex_2D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vertices;
		if (FAILED(Device->CreateBuffer(&bd, &InitData, &VertexBuffer)))
		{
			return E_FAIL;
		}
		//バーテックスバッファーをセット
		UINT stride = sizeof(Vertex_2D);
		UINT offset = 0;
		DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

		InitConstantBuffer();

		return S_OK;
	}


	//InitShader関数
	//シェーダのロードなど
	HRESULT Mesh_Sprite::InitConstantBuffer()
	{

		//コンスタントバッファー作成　ここでは変換行列渡し用
		D3D11_BUFFER_DESC cb;
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.ByteWidth = sizeof(CONSTANT_BUFFER_2D);
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.StructureByteStride = 0;
		cb.Usage = D3D11_USAGE_DYNAMIC;

		if (FAILED(Device->CreateBuffer(&cb, NULL, &ConstantBuffer)))
		{
			return E_FAIL;
		}

		D3D11_SAMPLER_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		Device->CreateSamplerState(&sd, &SamplerState);

		return S_OK;
	}

	
	//　Draw関数
	//　描画
	void Mesh_Sprite::Draw()
	{
		XMMATRIX World = XMMatrixScaling(Size.x, Size.y, Size.z);
		World *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(angle.x),
			XMConvertToRadians(angle.y), XMConvertToRadians(angle.z));
		World *= XMMatrixTranslation(Position.x, Position.y, Position.z);

		XMMATRIX View = camera->GetView();
		XMMATRIX Proj = camera->GetProj();

		XMMATRIX WVP = World * View*Proj;

		if (Texture)
		{
			World = XMMatrixScaling(textureFream.x, textureFream.y, 1.0);
			World *= XMMatrixTranslation(texureUV.x, texureUV.y, 0.0f);
			XMStoreFloat4x4(&M_Tex, World);

		}
		else M_Tex._44 = 0.0f;

		//使用するシェーダーのセット
		DeviceContext->VSSetShader(Shader->getVertexShader(), nullptr, 0);
		DeviceContext->PSSetShader(Shader->getPixelShader(), nullptr, 0);

		//シェーダーのコンスタントバッファーに各種データを渡す
		D3D11_MAPPED_SUBRESOURCE pData;
		CONSTANT_BUFFER_2D cb;
		if (SUCCEEDED(DeviceContext->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			//ワールド、カメラ、射影行列]を渡す
			//cb.W = World;
			cb.WVP = XMMatrixTranspose(WVP);
			cb.Tex = XMMatrixTranspose(XMLoadFloat4x4(&M_Tex));
			cb.Color = Color;

			rsize_t t = sizeof(cb);
			memcpy_s(pData.pData, 256, (void*)(&cb), sizeof(cb));
			DeviceContext->Unmap(ConstantBuffer, 0);
		}

		//このコンスタントバッファーをどのシェーダーで使うか
		DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);
		DeviceContext->PSSetConstantBuffers(0, 1, &ConstantBuffer);

		//頂点インプットレイアウトをセット
		DeviceContext->IASetInputLayout(Shader->getVertexLayout());

		UINT stride = sizeof(Vertex_2D);
		UINT offset = 0;
		DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

		//プリミティブ・トポロジーをセット
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		DeviceContext->PSSetSamplers(0, 1, &SamplerState);
		DeviceContext->PSSetShaderResources(0, 1, &Texture);

		//プリミティブをレンダリング
		DeviceContext->Draw(4, 0);

	}

	void Mesh_Sprite::RDraw(bool _flont)
	{
		Engine->addRenderList_2D(this, _flont);
		
	}

	void Mesh_Sprite::reset()
	{
		setColor(1, 1, 1);
		setPosition(XMFLOAT2());
		setalph(1);
		setangle(0);
		setUV();
		setUVF();
		setTexture(nullptr);

	}
}