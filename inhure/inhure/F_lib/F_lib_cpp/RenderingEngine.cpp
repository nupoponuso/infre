

//�C���N���[�h
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
    //�O���[�o���ϐ�
	RenderingEngine* Engine = nullptr;

	//�����_�����O�G���W���̃Q�b�^�[
	RenderingEngine* getEngine() { return Engine; }


	//RenderingEngine�N���X--------------------------------------------------

	//�R���X�g���N�^
	RenderingEngine::RenderingEngine()
	{
		Engine = this;
		s = nullptr;
		Efect = nullptr;
		nowBSteta = BLEND_NONE;

	}

	// �ǉ�
	RenderingEngine::~RenderingEngine()
	{
		::F_lib_Render::D2DText::Uninit();
		::D2DFunctions::D2DFuncComponent::Uninit();
		::F_lib_Render::RenderTargetResources::DeleteResources();
		delete D2DTextMng;
		delete D2DTargets;
	}
	// �����܂�

	//������
	//�X���b�v�`�F�C����f�o�C�X�R���e�L�X�g�Ȃǂ̍쐬
	void RenderingEngine::Iint(HWND _hWnd, int _width, int _height)
	{
		windowsize.x = (float)_width;
		windowsize.y = (float)_height;

		// �f�o�C�X,�f�o�C�X�R���e�L�X�g�ƃX���b�v�`�F�[���̍쐬
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


		UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;//��---�ύX--- DirectX11���Direct2D���g�p���邽�߂ɕK�v
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
			createDeviceFlags, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, &sd,
			&SwapChain, &Device, nullptr, &DeviceContext);


		//���C�������_�[�^�[�Q�b�g�̍쐬
		Mainterget = new RenderTerget();
		RenderTergetInitdate data;
		data.format_DSV = DXGI_FORMAT_D32_FLOAT;
		data.BackClearColor.x = 1;
		data.Create_TextureRTV = true;
		data.height = _height;
		data.wight = _width;
		Mainterget->Create(this, data);

		//�m���X�N���[�������_�����O�p�̃����_�[�^�[�Q�b�g�̍쐬
		nonScereen = new RenderTerget();
		data.format_RTV = DXGI_FORMAT_R11G11B10_FLOAT;//�F�f�[�^�o��
		data.BackClearColor.x = 1;
		data.BackClearColor.z = 1;
		data.Create_MainRTV = false;
		nonScereen->Create(this, data);

		//DepthScreen = new RenderTerget();
		//data.format_RTV = DXGI_FORMAT_R32_FLOAT;//�F�f�[�^�o��
		//data.BackClearColor.x = 0;
		//data.BackClearColor.z = 1;
		//data.Create_MainRTV = false;
		//DepthScreen->Create(this, data);

		// ���X�^���C�Y�ݒ�
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

		//�u�����h�X�e�[�g�ݒ�
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

		//�f�v�X�X�e���V���ݒ�
		CD3D11_DEFAULT def;
		CD3D11_DEPTH_STENCIL_DESC dsd(def);
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		Device->CreateDepthStencilState(&dsd, &DSState[0]);

		CD3D11_DEPTH_STENCIL_DESC dsd1(def);
		dsd1.DepthEnable = false;
		Device->CreateDepthStencilState(&dsd1, &DSState[1]);

		text = new Text();
		text->init(_hWnd, this);

		// �ǉ�
		// D2D�@�\�p�����_�[�^�[�Q�b�g��DWrite�p�t�@�N�g���̍쐬
		D2DTargets = new D2DRenderTargetsandDWrite();
		D2DTargets->Init(SwapChain, _hWnd);
		/*
		*	DxgiRenaderTarget�ł����@�\���Ȃ��B
		*	HwndRenderTarget,DCRenderTarget�ւ̑Ή��͂��Ă��Ȃ��̂Œ���
		*	(�����p���Ă���RenderingEngine(������)��RenderTerget.h�̐ݒ�Ɉ˂��Ă���)
		*/
		RenderTargetResources::Create(D2DTargets->GetDxgiRenderTarget());
		D2DTextMng = new ::F_lib_Render::D2DTextMng();
		D2DText::Init(D2DTargets->GetDWriteFactory(), D2DTextMng);
		::D2DFunctions::D2DFuncComponent::Init(D2DTargets->GetD2DFactory());

		// �����܂�

	}


	// addRenderList_3D�֐��@ 
	// �RD���f����`�惊�X�g�ɓo�^
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


	// addRenderBillList�֐��@ 
	// �r���{�[�h��`�惊�X�g�ɓo�^
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


	// addRenderList_2D�֐��@ 
	// 2D���f����`�惊�X�g�ɓo�^
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


	//�@Renderring�֐�
	//�@�S�Ă̕`����s��
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

		Mainterget->RenderClser(DeviceContext);		//�m���X�N���[�������_�����O���������X�v���C�g�ŕ`��
		D2DTargets->GetDxgiRenderTarget()->BeginDraw();	// D2D�̕`��J�n
														// �ďo�̓����_�[�^�[�Q�b�g�̃N���A��~SwapChain.Present()�̊Ԃ�1��̂�
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

		D2DTargets->GetDxgiRenderTarget()->EndDraw();	//D2D�̕`��I��
		SwapChain->Present(1, 0);//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj	
		Render3DList.clear();
		Render2DListBack.clear();
		Render2DListFlont.clear();
		RenderBillList.clear();
	}


	//setZBffer�֐�
	//���o�b�t�@�̐ݒ�
	void RenderingEngine::setZBffer(bool _use = false)
	{
		DeviceContext->OMSetDepthStencilState((_use) ? nullptr : DSState[1], 0);
	}


	//setZBfferW�֐�
	//���o�b�t�@�̐ݒ�
	void RenderingEngine::setZBfferW(bool _use)
	{
		DeviceContext->OMSetDepthStencilState((_use) ? nullptr : DSState[0], 0);
	}


	//setBlend�֐�
	//�u�����h�X�e�[�g�̐ݒ�
	void RenderingEngine::setBlend(int _Bstate = 0)
	{
		nowBSteta = (BlendSteta)_Bstate;

		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		DeviceContext->OMSetBlendState(BlendState[_Bstate], blendFactor, 0xffffffff);

	}


	//setRasterrize�֐�
	//���X�^���C�Y�ݒ�
	void RenderingEngine::setRasterrize(int _mode)
	{
		if (_mode != 0)
			DeviceContext->RSSetState(RState[_mode]);

	}


	//listRender�֐�
	//���X�g���̂RD���f���`��
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


	//listRender_Billbord�֐�
	//���X�g���̃r���{�[�h�`��
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


	//listRender_2D�֐�
	//���X�g���̃X�v���C�g�`��
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