//-------------------------------------------
//
// Effekseer�Ǘ��N���X�N���X 
//		auhor: hujioka tomoya
//
//		12/18�����܂���
//-------------------------------------------


//�C���N���[�h
#include "EffekseerManeger.h"
#include "Camera.h"

namespace F_lib_Render
{
	using namespace Effekseer;

	//�R���X�g���N�^
	//�l�̏�����
	EffekseerManeger::EffekseerManeger(ID3D11Device * _device, ID3D11DeviceContext *_deviceContext, Camera_3D* _camera) : camera(_camera)
	{
		rendarer = EffekseerRendererDX11::Renderer::Create(_device, _deviceContext, 8000);
		manager = Manager::Create(8000);

		// �`�惂�W���[���̐ݒ�
		manager->SetSpriteRenderer(rendarer->CreateSpriteRenderer());
		manager->SetRibbonRenderer(rendarer->CreateRibbonRenderer());
		manager->SetRingRenderer(rendarer->CreateRingRenderer());
		manager->SetTrackRenderer(rendarer->CreateTrackRenderer());
		manager->SetModelRenderer(rendarer->CreateModelRenderer());

		// �e�N�X�`���A���f���A�J�[�u�A�}�e���A�����[�_�[�̐ݒ肷��B
		// ���[�U�[���Ǝ��Ŋg���ł���B���݂̓t�@�C������ǂݍ���ł���B
		manager->SetTextureLoader(rendarer->CreateTextureLoader());
		manager->SetModelLoader(rendarer->CreateModelLoader());
		manager->SetMaterialLoader(rendarer->CreateMaterialLoader());
		manager->SetCurveLoader(MakeRefPtr<CurveLoader>());


		//�G�t�F�N�g��load
		manager->SetCoordinateSystem(CoordinateSystem::LH);
		Effekseer::EffectRef e;
		e = Effect::Create(manager, u"data/e/bana.efk");
		effect.push_back(e);

	}


	//update�֐�
	//�t���[�����ƂɍX�V����
	void EffekseerManeger::update()
	{
		manager->Update();
		static int time = 0;
		rendarer->SetTime(time / 60.0f);

	}


	//Draw�֐�
	//�G�ӂ��������̕`��
	void EffekseerManeger::Draw()
	{
		Vector3D eye = Vector3D(camera->GetPos().x, camera->GetPos().y, camera->GetPos().z);
		Vector3D look = Vector3D(camera->GetTergetPos().x, camera->GetTergetPos().y, camera->GetTergetPos().z);
		Vector3D up = Vector3D(camera->Getup().x, camera->Getup().y, camera->Getup().z);

		rendarer->SetProjectionMatrix(
			::Effekseer::Matrix44().PerspectiveFovLH(XMConvertToRadians(camera->GetProjd().x), camera->GetProjd().y, camera->GetProjd().z, camera->GetProjd().w));

		rendarer->SetCameraMatrix(::Effekseer::Matrix44().LookAtLH(eye, look, up));

		rendarer->BeginRendering();
		manager->Draw();
		rendarer->EndRendering();

	}


	//play�֐�
	//�G�ӂ��������̍Đ��@��������`�施�߂�����
	Handle EffekseerManeger::play(int _id, XMFLOAT3 _pos)
	{
		return manager->Play(effect[_id], _pos.x, _pos.y, _pos.z);
	}


	//play�֐�
	//�G�ӂ��������̍Đ��@��������`�施�߂�����
	Handle EffekseerManeger::play(int _id, XMFLOAT3 _pos, XMFLOAT3 _angle, XMFLOAT3 _Scle)
	{
		Handle h = manager->Play(effect[_id], _pos.x, _pos.y, _pos.z);
		setangle(h, _angle);
		setScale(h, _Scle);

		return h;
	}


	//play�֐�
	//�G�ӂ��������̍Đ��@��������`�施�߂�����
	Handle EffekseerManeger::play(int _id, XMFLOAT3 _pos, XMFLOAT3 _angle, float _Scle)
	{
		Handle h = manager->Play(effect[_id], _pos.x, _pos.y, _pos.z);
		setangle(h, _angle);
		setScale(h, _Scle);

		return h;
	}


	//�w�肵���G�t�F�N�g�̍Đ�
	void EffekseerManeger::setstop(Handle _handle)
	{
		manager->SetPaused(_handle, false);
		manager->SetShown(_handle, false);

	}


	//�w�肵���G�t�F�N�g�̈ʒu�̐ݒ�
	void EffekseerManeger::setposition(Handle _handle, XMFLOAT3 _pos)
	{
		manager->SetLocation(_handle, _pos.x, _pos.y, _pos.z);
	}


	//�w�肵���G�t�F�N�g�̉�]��ݒ�
	void EffekseerManeger::setangle(Handle _handle, XMFLOAT3 _angle)
	{
		manager->SetRotation(_handle, XMConvertToRadians(-_angle.x), XMConvertToRadians(_angle.y), XMConvertToRadians(_angle.z));
	}


	//�w�肵���G�t�F�N�g�̑傫�����w��
	void EffekseerManeger::setScale(Handle _handle, XMFLOAT3 _Scale)
	{
		manager->SetScale(_handle, _Scale.x, _Scale.y, _Scale.z);
	}


	//�w�肵���G�t�F�N�g�̑傫����ݒ�
	void EffekseerManeger::setScale(Handle _handle, float _Scale)
	{
		manager->SetScale(_handle, _Scale, _Scale, _Scale);
	}


	//�w�肵���G�t�F�N�g�̐F��ς���
	void EffekseerManeger::setColor(Handle _handle, XMFLOAT3 _Color)
	{
		Color c = Color(uint8_t(255 * _Color.x), uint8_t(255 * _Color.y), uint8_t(255 * _Color.z));
		manager->SetAllColor(_handle, c);

	}

	void EffekseerManeger::setColor(Handle _handle, XMFLOAT4 _Color)
	{
		Color c = Color(uint8_t(255 * _Color.x), uint8_t(255 * _Color.y), uint8_t(255 * _Color.z), uint8_t(255 * _Color.w));
		manager->SetAllColor(_handle, c);

	}


	//�w�肵���G�t�F�N�g�̐��l��ς���
	void EffekseerManeger::setdate(Handle _handle, XMFLOAT3 _pos, XMFLOAT3 _angle, XMFLOAT3 _scale)
	{
		manager->SetLocation(_handle, _pos.x, _pos.y, _pos.z);
		manager->SetRotation(_handle, XMConvertToRadians(_angle.x), XMConvertToRadians(_angle.y), XMConvertToRadians(_angle.z));
		manager->SetScale(_handle, _scale.x, _scale.y, _scale.z);

	}


	//�w�肵���G�t�F�N�g�̃C���X�^���X�����邩���ׂ�
	bool EffekseerManeger::getinstance(Handle _handle)
	{
		return manager->Exists(_handle);
	}

}