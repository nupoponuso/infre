//-------------------------------------------
//
//		ビルボードクラス 
//		auhor: hujioka tomoya
//		
//-------------------------------------------

//インクルード
#include "Mesh_billbord.h"
#include "Camera.h"
#include "Mesh_ShaderDat.h"
#include "RenderingEngine.h"


namespace F_lib_Render
{
	//コンストラクタ
	//値の初期化
	Mesh_billbord::Mesh_billbord(ID3D11Device * _Device, ID3D11DeviceContext * _DeviceContext, Camera_3D * _Camera) :Mesh_Sprite(_Device, _DeviceContext, _Camera)
	{}


	//draw関数
	void Mesh_billbord::Draw()
	{
		XMMATRIX World, View, Proj;

		View = camera->GetView();

		XMFLOAT4X4 ViewRot;
		XMStoreFloat4x4(&ViewRot, View);
		ViewRot._41 = ViewRot._42 = ViewRot._43 = 0;

		World = XMMatrixScaling(Size.x, Size.y, Size.z);
		World *= XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
		World *= XMMatrixInverse(0, XMLoadFloat4x4(&ViewRot));
		World *= XMMatrixTranslation(Position.x, Position.y, Position.z);

		Proj = camera->GetProj();

		XMMATRIX WVP = World * View * Proj;

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
			memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
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
	void Mesh_billbord::RDraw()
	{
		Engine->addRenderBillList(this);

	}
}