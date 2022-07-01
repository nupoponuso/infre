

//インクルード
#include "RenderingEngine.h"
#include "Mesh_ShaderDat.h"
#include "Text.h"

#include "../D2DRenderTargetsAndDWrite.h"
#include "../D2DDrawMng.h"
#include "../RenderTargetResources.h"
#include "../D2DText.h"
#include "../D2DFunctions.h"

namespace F_lib_Render
{
    //グローバル変数
	RenderingEngine* Engine = nullptr;

	//レンダリングエンジンのゲッター
	RenderingEngine* getEngine() { return Engine; }


	//RenderingEngineクラス--------------------------------------------------

	//コンストラクタ
	RenderingEngine::RenderingEngine()
	{
		Engine = this;
		s = nullptr;
		Efect = nullptr;
		nowBSteta = BLEND_NONE;

	}

	// 追加
	RenderingEngine::~RenderingEngine()
	{
		::F_lib_Render::D2DText::Uninit();
		::D2DFunctions::D2DFuncComponent::Uninit();
		::F_lib_Render::RenderTargetResources::DeleteResources();
		delete D2DTextMng;
		delete D2DTargets;
	}
	// ここまで

	//初期化
	//スワップチェインやデバイスコンテキストなどの作成
	void RenderingEngine::Iint(HWND _hWnd, int _width, int _height)
	{
		windowsize.x = (float)_width;
		windowsize.y = (float)_height;

		// デバイス,デバイスコンテキストとスワップチェーンの作成
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = _width;
		sd.BufferDesc.Height = _height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = _hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = true;

		D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};


		UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;//★---変更--- DirectX11上でDirect2Dを使用するために必要
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
			createDeviceFlags, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, &sd,
			&SwapChain, &Device, nullptr, &DeviceContext);


		//メインレンダーターゲットの作成
		Mainterget = new RenderTerget();
		RenderTergetInitdate data;
		data.format_DSV = DXGI_FORMAT_D32_FLOAT;
		data.BackClearColor.x = 1;
		data.Create_TextureRTV = true;
		data.height = _height;
		data.wight = _width;
		Mainterget->Create(this, data);

		//ノンスクリーンレンダリング用のレンダーターゲットの作成
		nonScereen = new RenderTerget();
		data.format_RTV = DXGI_FORMAT_R11G11B10_FLOAT;//色データ出力
		data.BackClearColor.x = 1;
		data.BackClearColor.z = 1;
		data.Create_MainRTV = false;
		nonScereen->Create(this, data);

		//DepthScreen = new RenderTerget();
		//data.format_RTV = DXGI_FORMAT_R32_FLOAT;//色データ出力
		//data.BackClearColor.x = 0;
		//data.BackClearColor.z = 1;
		//data.Create_MainRTV = false;
		//DepthScreen->Create(this, data);

		// ラスタライズ設定
		D3D11_RASTERIZER_DESC rd;
		ZeroMemory(&rd, sizeof(rd));
		rd.FillMode = D3D11_FILL_SOLID; //rd.FillMode = D3D11_FILL_WIREFRAME;
		rd.CullMode = D3D11_CULL_NONE;
		Device->CreateRasterizerState(&rd, &RState[0]);

		rd.CullMode = D3D11_CULL_FRONT;
		Device->CreateRasterizerState(&rd, &RState[1]);

		rd.CullMode = D3D11_CULL_BACK;
		Device->CreateRasterizerState(&rd, &RState[2]);

		DeviceContext->RSSetState(RState[2]);

		//ブレンドステート設定
		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.IndependentBlendEnable = false;
		bd.AlphaToCoverageEnable = false;
		bd.RenderTarget[0].BlendEnable = false;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Device->CreateBlendState(&bd, &BlendState[0]);

		bd.RenderTarget[0].BlendEnable = true;
		Device->CreateBlendState(&bd, &BlendState[1]);

		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		Device->CreateBlendState(&bd, &BlendState[2]);

		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
		Device->CreateBlendState(&bd, &BlendState[3]);

		//デプスステンシル設定
		CD3D11_DEFAULT def;
		CD3D11_DEPTH_STENCIL_DESC dsd(def);
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		Device->CreateDepthStencilState(&dsd, &DSState[0]);

		CD3D11_DEPTH_STENCIL_DESC dsd1(def);
		dsd1.DepthEnable = false;
		Device->CreateDepthStencilState(&dsd1, &DSState[1]);

		text = new Text();
		text->init(_hWnd, this);

		// 追加
		// D2D機能用レンダーターゲットとDWrite用ファクトリの作成
		D2DTargets = new D2DRenderTargetsandDWrite();
		D2DTargets->Init(SwapChain, _hWnd);
		/*
		*	DxgiRenaderTargetでしか機能しない。
		*	HwndRenderTarget,DCRenderTargetへの対応はしていないので注意
		*	(今利用しているRenderingEngine(藤岡製)のRenderTerget.hの設定に依っている)
		*/
		RenderTargetResources::Create(D2DTargets->GetDxgiRenderTarget());
		D2DTextMng = new ::F_lib_Render::D2DTextMng();
		D2DText::Init(D2DTargets->GetDWriteFactory(), D2DTextMng);
		::D2DFunctions::D2DFuncComponent::Init(D2DTargets->GetD2DFactory());

		// ここまで

	}


	// addRenderList_3D関数　 
	// ３Dモデルを描画リストに登録
	void RenderingEngine::addRenderList_3D(Mesh_Fbx * _mesh)
	{
		RenderingDat_3D dat;

		dat.mesh = _mesh;
		dat.animeDat = _mesh->getanime();
		dat.Shader = _mesh->getShader();
		dat.pos = _mesh->getPosition();
		dat.size = _mesh->getsize();
		dat.angle = _mesh->getangle();

		Render3DList.push_back(dat);

	}


	// addRenderBillList関数　 
	// ビルボードを描画リストに登録
	void RenderingEngine::addRenderBillList(Mesh_billbord * _b)
	{
		RenderingDat_Billbord dat;

		dat.pos = _b->getPosition();
		dat.size = XMFLOAT2(_b->getsize().x, _b->getsize().y);
		dat.angle = _b->getangle().z;
		dat.UV = _b->getUV();
		dat.UVF = _b->getUVF();
		dat.Color = _b->getColor();
		dat.Shader = _b->getShader();
		dat.textre = _b->getTexture();

		RenderBillList.push_back(dat);

	}


	// addRenderList_2D関数　 
	// 2Dモデルを描画リストに登録
	void RenderingEngine::addRenderList_2D(Mesh_Sprite* _s, bool _flont)
	{
		RenderingDat_2D dat;
	
		dat.BS = nowBSteta;
		dat.Shader = _s->getShader();
		dat.textre = _s->getTexture();
		dat.pos = XMFLOAT2(_s->getPosition().x, _s->getPosition().y);
		dat.size = XMFLOAT2(_s->getsize().x, _s->getsize().y);
		dat.angle = _s->getangle().z;
		dat.UV = _s->getUV();
		dat.UVF = _s->getUVF();
		dat.Color = _s->getColor();

		if (_flont) Render2DListFlont.push_back(dat);
		else        Render2DListBack.push_back(dat);

	}


	//　Renderring関数
	//　全ての描画を行う
	void RenderingEngine::Renderring()
	{
		Efect->update();
		s->getcamera()->update();
		s->reset();

		nonScereen->RenderClser(DeviceContext);

		listRender_2D(false);

		listRender_3D();
		Efect->Draw();
		listRender_Billbord();

		listRender_2D(true);

		Mainterget->RenderClser(DeviceContext);		//ノンスクリーンレンダリングした物をスプライトで描画
		D2DTargets->GetDxgiRenderTarget()->BeginDraw();	// D2Dの描画開始
														// 呼出はレンダーターゲットのクリア後~SwapChain.Present()の間に1回のみ
		setRasterrize(RASTER_BACK);
		setBlend(BLEND_ALPHABLEND);
		setZBffer(false);
		s->reset();
	
		s->setTexture(nonScereen->getTexture());
		s->setSize(windowsize);
		s->setPosition(0, 0);
		s->Draw();
		
		text->render();
		D2DTextMng->Render();

		D2DTargets->GetDxgiRenderTarget()->EndDraw();	//D2Dの描画終了
		SwapChain->Present(1, 0);//画面更新（バックバッファをフロントバッファに）	
		Render3DList.clear();
		Render2DListBack.clear();
		Render2DListFlont.clear();
		RenderBillList.clear();
	}


	//setZBffer関数
	//ｚバッファの設定
	void RenderingEngine::setZBffer(bool _use = false)
	{
		DeviceContext->OMSetDepthStencilState((_use) ? nullptr : DSState[1], 0);
	}


	//setZBfferW関数
	//ｚバッファの設定
	void RenderingEngine::setZBfferW(bool _use)
	{
		DeviceContext->OMSetDepthStencilState((_use) ? nullptr : DSState[0], 0);
	}


	//setBlend関数
	//ブレンドステートの設定
	void RenderingEngine::setBlend(int _Bstate = 0)
	{
		nowBSteta = (BlendSteta)_Bstate;

		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		DeviceContext->OMSetBlendState(BlendState[_Bstate], blendFactor, 0xffffffff);

	}


	//setRasterrize関数
	//ラスタライズ設定
	void RenderingEngine::setRasterrize(int _mode)
	{
		if (_mode != 0)
			DeviceContext->RSSetState(RState[_mode]);

	}


	//listRender関数
	//リスト内の３Dモデル描画
	void RenderingEngine::listRender_3D()
	{
		setBlend(BLEND_NONE);
		setZBffer(true);
		setRasterrize(RASTER_FLONT);

		for (auto dat : Render3DList)
		{
			dat.mesh->setPosition(dat.pos);
			dat.mesh->setSize(dat.size);
			dat.mesh->setangle(dat.angle);
			dat.mesh->setanime(dat.animeDat);
			dat.mesh->setShader(dat.Shader);
			dat.mesh->Draw();

		}

	}


	//listRender_Billbord関数
	//リスト内のビルボード描画
	void RenderingEngine::listRender_Billbord()
	{
		setRasterrize(RASTER_BACK);
		setZBffer(true);
		setBlend(BLEND_ALPHABLEND);
		b->reset();

		for (auto dat : RenderBillList)
		{
			b->setPosition(dat.pos);
			b->setangle(dat.angle);
			b->setColor(dat.Color);
			b->setTexture(dat.textre);
			b->setShader(dat.Shader);
			b->setSize(dat.size);
			b->setangle(dat.angle);
			b->setUV(dat.UV);
			b->setUVF(dat.UVF);
			b->Draw();

		}

	}


	//listRender_2D関数
	//リスト内のスプライト描画
	void RenderingEngine::listRender_2D(bool _flont)
	{
		setRasterrize(RASTER_BACK);
		setZBffer(false);
		setBlend(BLEND_ALPHABLEND);

		s->reset();

		for (auto dat : ((_flont) ? Render2DListFlont : Render2DListBack))
		{
			if (dat.BS != nowBSteta)
				setBlend(dat.BS);

			s->setShader(dat.Shader);
			s->setColor(dat.Color);
			s->setTexture(dat.textre);
			s->setPosition(dat.pos);
			s->setSize(dat.size);
			s->setangle(dat.angle);
			s->setUV(dat.UV);
			s->setUVF(dat.UVF);
			s->Draw();

		}
		
	}

	//--------------------------------------------------
}