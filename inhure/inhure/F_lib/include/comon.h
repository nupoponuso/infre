

#pragma once

//インクルード
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include <tchar.h>
#include <mmsystem.h>


//ライブラリのロード
#pragma comment(lib, "winmm")
#pragma comment(lib, "imm32")
#pragma comment(lib,"d3d11")
#pragma comment(lib, "d3dcompiler")
//#pragma comment(lib, "xaudio2.lib")


//名前空間の宣言
using namespace DirectX;

//マクロ定義
#define SAFE_RELEASE(x) if(x) {x->Release(); x=nullptr;}

#define sindeg(_angle) (sinf(XMConvertToRadians(_angle))) 
#define cosdeg(_angle) (cosf(XMConvertToRadians(_angle))) 


//ブレンドステート用enum
enum BlendSteta
{
	BLEND_NONE =0,
	BLEND_ALPHABLEND,
	BLEND_ADDITIVE,
	BLEND_SUBTRACTION,

	BLEND_MAX
};


//ラスタライズステート用enum
enum RasterrizeMode
{
	RASTER_NONE = 0,
	RASTER_FLONT,
	RASTER_BACK,

	RASTER_MAX
};


//--------------------
//
//	GameWindrawインスタンスに対して行う操作
//
//--------------------
