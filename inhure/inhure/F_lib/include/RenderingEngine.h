

#pragma once


//インクルード
#include "comon.h"
#include <vector>
#include "ResderTerget.h"
#include "Mesh_Fbxmodel.h"
#include "Mesh_Sprite.h"
#include "EffekseerManeger.h"

//
struct RenderingDat_3D
{
	F_lib_Render::Mesh_Fbx* mesh;
	F_lib_Render::Mesh_Fbx_anime* animeDat;
	F_lib_Render::Mesh_ShaderDat* Shader;

	XMFLOAT3 pos, size, angle;

};

struct RenderingDat_2D
{
	BlendSteta BS;

	F_lib_Render::Mesh_ShaderDat* Shader;
	ID3D11ShaderResourceView* textre;
	XMFLOAT2 pos, size, UV, UVF;
	XMFLOAT4 Color;
	float angle;

	RenderingDat_2D()
	{
		BS = BLEND_MAX;
	}

};



namespace F_lib_Render
{
	class RenderTerget;

	RenderingEngine* getEngine();

	//
	class RenderingEngine
	{
	public:
		RenderingEngine();

		void Iint(HWND, int _width,int _height);

		void addRenderList_3D(Mesh_Fbx*);
		void addRenderList_2D(Mesh_Sprite*,bool);
		void Renderring();

		void setZBffer(bool);
		void setZBfferW(bool);
		void setBlend(int);
		void setRasterrize(int);

		void setSprite(Mesh_Sprite* _s) { s = _s; }
		void setEfect(EffekseerManeger* _Efect) { Efect = _Efect; }

		ID3D11Device* getDevice() { return Device; }
		ID3D11DeviceContext* getDeviceContext() { return DeviceContext; }
		IDXGISwapChain*	getSwapChain() { return SwapChain; }
		XMFLOAT2 getWindowsize() { return windowsize; }
		class Text* getText() { return text; }

	private:
		void listRender_3D();
		void listRender_2D(bool);

		RenderTerget* Mainterget, *nonScereen;
		IDXGISwapChain*	SwapChain;
		ID3D11Device*			 Device;
		ID3D11DeviceContext*	 DeviceContext;

		ID3D11BlendState*		 BlendState[BlendSteta::BLEND_MAX];
		ID3D11DepthStencilState* DSState[2];
		ID3D11RasterizerState*   RState[3];

		BlendSteta nowBSteta;

		std::vector<RenderingDat_3D> Render3DList;
		std::vector<RenderingDat_2D> Render2DListBack, Render2DListFlont;

		class Text* text;
		Mesh_Sprite* s;
		EffekseerManeger* Efect;
		Mesh_ShaderDat*Shader;
		XMFLOAT2 windowsize;

	};
}