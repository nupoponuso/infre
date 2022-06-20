
//インクルード
#include "ResderTerget.h"
#include "RenderingEngine.h"

namespace F_lib_Render
{
	//コンストラクタ
	//
	RenderTerget::RenderTerget() :TexRTV(nullptr), TexDSV(nullptr), RTVTex(nullptr), DSVTex(nullptr), TexSRV(nullptr)
	{ }


	//Create関数
	//レンダーターゲットの作成
	void RenderTerget::Create(RenderingEngine * _Engine, RenderTergetInitdate _initdate)
	{
		ID3D11Device* _device = _Engine->getDevice();

		//スワップチェインからテクスチャのコピーかクラス内制作
		if (_initdate.Create_MainRTV)
			_Engine->getSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&RTVTex);

		else
		{
			D3D11_TEXTURE2D_DESC tdesc;
			tdesc.Width = _initdate.wight;
			tdesc.Height = _initdate.height;
			tdesc.MipLevels = 1;
			tdesc.ArraySize = 1;
			tdesc.MiscFlags = 0;
			tdesc.Format = _initdate.format_RTV;
			tdesc.SampleDesc.Count = 1;
			tdesc.SampleDesc.Quality = 0;
			tdesc.Usage = D3D11_USAGE_DEFAULT;
			tdesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			tdesc.CPUAccessFlags = 0;

			_device->CreateTexture2D(&tdesc, nullptr, &RTVTex);

		}

		//レンダーターゲットビューの作成
		_device->CreateRenderTargetView(RTVTex, nullptr, &TexRTV);

		//深度ステンシルビューの生成
		D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width = _initdate.wight;
		descDepth.Height = _initdate.height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = _initdate.format_DSV;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;// | D3D11_BIND_SHADER_RESOURCE;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		_device->CreateTexture2D(&descDepth, nullptr, &DSVTex);

		// Zバッファターゲットビュー生成
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

		//そのテクスチャーに対しデプスステンシルビュー(DSV)を作成
		_device->CreateDepthStencilView(DSVTex, &dsvd, &TexDSV);


		if (_initdate.Create_TextureRTV)
		{
			if (_initdate.fromat_TSRV == DXGI_FORMAT_UNKNOWN)
				_initdate.fromat_TSRV = _initdate.format_RTV;

			if (_initdate.format_RTV == _initdate.fromat_TSRV)
				_device->CreateShaderResourceView(RTVTex, nullptr, &TexSRV);
			else
			{
				D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
				ZeroMemory(&SRVDesc, sizeof(SRVDesc));
				SRVDesc.Format = _initdate.fromat_TSRV;
				SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				SRVDesc.Texture2D.MipLevels = 1;

				_device->CreateShaderResourceView(RTVTex, &SRVDesc, &TexSRV);

			}

		}

		vp.Width = (float)_initdate.wight;
		vp.Height = (float)_initdate.height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;

		BackClearColor = new  float[4]{ _initdate.BackClearColor.x,_initdate.BackClearColor.y ,_initdate.BackClearColor.z ,1 };

		RenderClser(_Engine->getDeviceContext());

	}


	//RenderClser関数
	//レンダリングのクリア
	void RenderTerget::RenderClser(ID3D11DeviceContext* _dc)
	{
		_dc->RSSetViewports(1, &vp);
		_dc->OMSetRenderTargets(1, &TexRTV, TexDSV);
		_dc->ClearRenderTargetView(TexRTV, BackClearColor);
		_dc->ClearDepthStencilView(TexDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	}


	//getTexture関数
	//レンダリングした画像の取得
	ID3D11ShaderResourceView * RenderTerget::getTexture()
	{
		return TexSRV;

	}
}