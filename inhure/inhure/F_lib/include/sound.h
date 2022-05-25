//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "comon.h"

#include <xaudio2.h>
// Windows7�̏ꍇ�͏�L���폜���Ĉȉ��ɒu������.
//#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xaudio2.h>

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,	// BGM0
	//SOUND_LABEL_BGM001,		// BGM1
	//SOUND_LABEL_BGM002, 	
	//SOUND_LABEL_BGM003,		
	//SOUND_LABEL_BGM004,	
	//SOUND_LABEL_BGM005,		
	//
	//SOUND_LABEL_SE,
	//SOUND_LABEL_SE_,
	//SOUND_LABEL_SE_SHOT4,		
	//SOUND_LABEL_SE_SRASH,		
	//SOUND_LABEL_SE_EXPLOSION,	
	//SOUND_LABEL_SE_SHRASH,	

	SOUND_LABEL_MAX,			// �o�^���̎����ݒ�
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label);	// �Đ�

void StopSound(SOUND_LABEL label);		// 1��~
void StopSound(void);					// �S����~
void PauseSound( void );				// �ꎞ��~
void ResumeSound( void );				// �ĊJ

void SetVolume(float fVol);				// ���ʒ���

#endif
