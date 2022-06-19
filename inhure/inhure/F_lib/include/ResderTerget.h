#pragma once

#include "comon.h"

namespace F_lib_Render
{

	struct RenderTergetInitdate
	{
		DXGI_FORMAT format_RTV, format_DSV, fromat_TSRV;
		int wight, height;
		XMFLOAT3 BackClearColor;
		bool Create_MainRTV, Create_TextureRTV;

		RenderTergetInitdate()
		{
			fromat_TSRV = DXGI_FORMAT_UNKNOWN;
			Create_MainRTV = true;
			Create_TextureRTV = false;
			wight = height = 500;

		}

	};

	class RenderTerget
	{
	public:
		RenderTerget();
		void Create(class RenderingEngine* _Engine, RenderTergetInitdate);
		void RenderClser(ID3D11DeviceContext*);

		ID3D11ShaderResourceView* getTexture();

	private:
		ID3D11RenderTargetView*	  TexRTV;
		ID3D11DepthStencilView*   TexDSV;
		ID3D11Texture2D*		  RTVTex;
		ID3D11Texture2D*		  DSVTex;
		ID3D11ShaderResourceView* TexSRV;

		D3D11_VIEWPORT vp;

		float* BackClearColor;

	};

}