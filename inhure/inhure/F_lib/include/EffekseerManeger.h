//-------------------------------------------
//
// 　Effekseer管理クラスクラス | EffekseerManeger.cpp |
//		auhor: hujioka tomoya
//
//		12/18書きました
//-------------------------------------------

#pragma once

//インクルード
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <vector>
#include "comon.h"



//ライブラリのロード
#ifdef _DEBUG
#pragma comment(lib, "EffekseerD.lib")
#pragma comment(lib, "EffekseerRendererDX11D.lib")
#else
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX11.lib")
#endif


namespace F_lib_Render
{
	//EffekseerManegerクラス
	//クラスメンバ
	class EffekseerManeger
	{
	public:
		EffekseerManeger(ID3D11Device*, ID3D11DeviceContext*,class Camera_3D*);

		void update();
		void Draw();

		//引数：エフェクトid,位置,角度,サイズ
		Effekseer::Handle play(int, XMFLOAT3);

		//引数：エフェクトid,位置,角度,サイズ
		Effekseer::Handle play(int, XMFLOAT3, XMFLOAT3, XMFLOAT3);
		//引数：エフェクトid,位置,角度,サイズ
		Effekseer::Handle play(int, XMFLOAT3, XMFLOAT3, float);

		void setstop(Effekseer::Handle);

		void setposition(Effekseer::Handle, XMFLOAT3);
		void setangle(Effekseer::Handle, XMFLOAT3);
		void setScale(Effekseer::Handle, XMFLOAT3);
		void setScale(Effekseer::Handle, float);

		void setColor(Effekseer::Handle, XMFLOAT3);
		void setColor(Effekseer::Handle, XMFLOAT4);

		void setdate(Effekseer::Handle, XMFLOAT3, XMFLOAT3, XMFLOAT3);

		bool getinstance(Effekseer::Handle);


	private:
		class Camera_3D* camera;

		EffekseerRendererDX11::RendererRef rendarer;
		Effekseer::ManagerRef manager;
		std::vector<Effekseer::EffectRef>  effect;
		
		int time = 0;
	};

}