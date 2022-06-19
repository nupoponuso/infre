//-------------------------------------------
//
//	 DirectX11�p��light�N���X�Q
//		auhor: hujioka tomoya
//		
//-------------------------------------------


//�C���N���[�h
#include "Light.h"
#include "RenderingEngine.h"

namespace F_lib_Render
{
	//Light�N���X-----------------------------------------


	//�R���X�g���N�^
	//�l�̏�����
	Light::Light() : LightDir(XMFLOAT4(-0.5, -1, 1, 1)), Anbient(XMFLOAT4(1.0, 1.0f, 1.0f, 1.0f))
	{ }


	//-----------------------------------------

	//Light_Point�N���X-----------------------------------------

	//�R���X�g���N�^
	//�l�̏�����
	Light_Point::Light_Point(Camera_3D* _c) : Light(), c(_c)
	{

	}


	//�f�X�g���N�^
	Light_Point::~Light_Point()
	{ }


	//init�֐�
	//�R���X�^���g�o�b�t�@�쐬
	void Light_Point::init(F_lib_Render::RenderingEngine* _engine)
	{
		DeviceContext = _engine->getDeviceContext();

		//�R���X�^���g�o�b�t�@�[�쐬�@�����ł͕ϊ��s��n���p
		D3D11_BUFFER_DESC cb;
		cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cb.ByteWidth = sizeof(CONSTANT_BUFFER_Light);
		cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cb.MiscFlags = 0;
		cb.Usage = D3D11_USAGE_DYNAMIC;

		_engine->getDevice()->CreateBuffer(&cb, nullptr, &ConstantBufferL);

		LightPos = XMFLOAT3(0, 300, 0);

		XMFLOAT4X4 UV44;
		ZeroMemory(&UV44, sizeof(XMFLOAT4X4));

		UV44._12 = UV44._13 = UV44._14 = 0;
		UV44._21 = UV44._23 = UV44._24 = 0;
		UV44._31 = UV44._32 = UV44._34 = 0;
		UV44._43 = 0;

		UV44._22 = -0.5;
		UV44._33 = UV44._44 = 1;
		UV44._11 = UV44._41 = UV44._42 = 0.5;

		UV = XMLoadFloat4x4(&UV44);

	}


	//update�֐�
	//�R���X�^���g�o�b�t�@
	void Light_Point::update()
	{
		World = XMMatrixRotationRollPitchYaw(XMConvertToRadians(90), XMConvertToRadians(0), XMConvertToRadians(0));
		World *= XMMatrixTranslation(LightPos.x, LightPos.y, LightPos.z);
		World = XMMatrixInverse(0, World);

		//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
		D3D11_MAPPED_SUBRESOURCE pData;
		CONSTANT_BUFFER_Light cl;
		if (SUCCEEDED(DeviceContext->Map(ConstantBufferL, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
		{
			//���[���h�A�J�����A�ˉe�s���n��
			cl.LightPos = LightDir;
			cl.eyePos = XMFLOAT4(c->GetPos().x, c->GetPos().y, c->GetPos().z, 0);
			cl.LightAnbient = Anbient;

			memcpy_s(pData.pData, pData.RowPitch, (void*)(&cl), sizeof(CONSTANT_BUFFER_Light));
			DeviceContext->Unmap(ConstantBufferL, 0);
		}

		DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBufferL);
		DeviceContext->PSSetConstantBuffers(0, 1, &ConstantBufferL);

	}

	//-----------------------------------------
}