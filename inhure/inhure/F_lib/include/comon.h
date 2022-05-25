

#pragma once

//�C���N���[�h
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include <tchar.h>
#include <mmsystem.h>


//���C�u�����̃��[�h
#pragma comment(lib, "winmm")
#pragma comment(lib, "imm32")
#pragma comment(lib,"d3d11")
#pragma comment(lib, "d3dcompiler")
//#pragma comment(lib, "xaudio2.lib")


//���O��Ԃ̐錾
using namespace DirectX;

//�}�N����`
#define SAFE_RELEASE(x) if(x) {x->Release(); x=nullptr;}

#define sindeg(_angle) (sinf(XMConvertToRadians(_angle))) 
#define cosdeg(_angle) (cosf(XMConvertToRadians(_angle))) 


//�u�����h�X�e�[�g�penum
enum BlendSteta
{
	BLEND_NONE =0,
	BLEND_ALPHABLEND,
	BLEND_ADDITIVE,
	BLEND_SUBTRACTION,

	BLEND_MAX
};


//���X�^���C�Y�X�e�[�g�penum
enum RasterrizeMode
{
	RASTER_NONE = 0,
	RASTER_FLONT,
	RASTER_BACK,

	RASTER_MAX
};


//--------------------
//
//	GameWindraw�C���X�^���X�ɑ΂��čs������
//
//--------------------
