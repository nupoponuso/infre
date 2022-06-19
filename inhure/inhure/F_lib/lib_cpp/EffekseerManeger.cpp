//-------------------------------------------
//
// Effekseer管理クラスクラス 
//		auhor: hujioka tomoya
//
//		12/18書きました
//-------------------------------------------


//インクルード
#include "EffekseerManeger.h"
#include "Camera.h"

namespace F_lib_Render
{
	using namespace Effekseer;

	//コンストラクタ
	//値の初期化
	EffekseerManeger::EffekseerManeger(ID3D11Device * _device, ID3D11DeviceContext *_deviceContext, Camera_3D* _camera) : camera(_camera)
	{
		rendarer = EffekseerRendererDX11::Renderer::Create(_device, _deviceContext, 8000);
		manager = Manager::Create(8000);

		// 描画モジュールの設定
		manager->SetSpriteRenderer(rendarer->CreateSpriteRenderer());
		manager->SetRibbonRenderer(rendarer->CreateRibbonRenderer());
		manager->SetRingRenderer(rendarer->CreateRingRenderer());
		manager->SetTrackRenderer(rendarer->CreateTrackRenderer());
		manager->SetModelRenderer(rendarer->CreateModelRenderer());

		// テクスチャ、モデル、カーブ、マテリアルローダーの設定する。
		// ユーザーが独自で拡張できる。現在はファイルから読み込んでいる。
		manager->SetTextureLoader(rendarer->CreateTextureLoader());
		manager->SetModelLoader(rendarer->CreateModelLoader());
		manager->SetMaterialLoader(rendarer->CreateMaterialLoader());
		manager->SetCurveLoader(MakeRefPtr<CurveLoader>());


		//エフェクトのload
		manager->SetCoordinateSystem(CoordinateSystem::LH);
		Effekseer::EffectRef e;
		e = Effect::Create(manager, u"data/e/bana.efk");
		effect.push_back(e);

	}


	//update関数
	//フレームごとに更新する
	void EffekseerManeger::update()
	{
		manager->Update();
		static int time = 0;
		rendarer->SetTime(time / 60.0f);

	}


	//Draw関数
	//絵ふぇくしあの描画
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


	//play関数
	//絵ふぇくしあの再生　引数から描画命令をする
	Handle EffekseerManeger::play(int _id, XMFLOAT3 _pos)
	{
		return manager->Play(effect[_id], _pos.x, _pos.y, _pos.z);
	}


	//play関数
	//絵ふぇくしあの再生　引数から描画命令をする
	Handle EffekseerManeger::play(int _id, XMFLOAT3 _pos, XMFLOAT3 _angle, XMFLOAT3 _Scle)
	{
		Handle h = manager->Play(effect[_id], _pos.x, _pos.y, _pos.z);
		setangle(h, _angle);
		setScale(h, _Scle);

		return h;
	}


	//play関数
	//絵ふぇくしあの再生　引数から描画命令をする
	Handle EffekseerManeger::play(int _id, XMFLOAT3 _pos, XMFLOAT3 _angle, float _Scle)
	{
		Handle h = manager->Play(effect[_id], _pos.x, _pos.y, _pos.z);
		setangle(h, _angle);
		setScale(h, _Scle);

		return h;
	}


	//指定したエフェクトの再生
	void EffekseerManeger::setstop(Handle _handle)
	{
		manager->SetPaused(_handle, false);
		manager->SetShown(_handle, false);

	}


	//指定したエフェクトの位置の設定
	void EffekseerManeger::setposition(Handle _handle, XMFLOAT3 _pos)
	{
		manager->SetLocation(_handle, _pos.x, _pos.y, _pos.z);
	}


	//指定したエフェクトの回転を設定
	void EffekseerManeger::setangle(Handle _handle, XMFLOAT3 _angle)
	{
		manager->SetRotation(_handle, XMConvertToRadians(-_angle.x), XMConvertToRadians(_angle.y), XMConvertToRadians(_angle.z));
	}


	//指定したエフェクトの大きさを指定
	void EffekseerManeger::setScale(Handle _handle, XMFLOAT3 _Scale)
	{
		manager->SetScale(_handle, _Scale.x, _Scale.y, _Scale.z);
	}


	//指定したエフェクトの大きさを設定
	void EffekseerManeger::setScale(Handle _handle, float _Scale)
	{
		manager->SetScale(_handle, _Scale, _Scale, _Scale);
	}


	//指定したエフェクトの色を変える
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


	//指定したエフェクトの数値を変える
	void EffekseerManeger::setdate(Handle _handle, XMFLOAT3 _pos, XMFLOAT3 _angle, XMFLOAT3 _scale)
	{
		manager->SetLocation(_handle, _pos.x, _pos.y, _pos.z);
		manager->SetRotation(_handle, XMConvertToRadians(_angle.x), XMConvertToRadians(_angle.y), XMConvertToRadians(_angle.z));
		manager->SetScale(_handle, _scale.x, _scale.y, _scale.z);

	}


	//指定したエフェクトのインスタンスがあるか調べる
	bool EffekseerManeger::getinstance(Handle _handle)
	{
		return manager->Exists(_handle);
	}

}