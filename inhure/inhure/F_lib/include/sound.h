//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "comon.h"

#include <xaudio2.h>
// Windows7の場合は上記を削除して以下に置き換え.
//#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xaudio2.h>

//*****************************************************************************
// サウンドファイル
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

	SOUND_LABEL_MAX,			// 登録数の自動設定
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label);	// 再生

void StopSound(SOUND_LABEL label);		// 1つ停止
void StopSound(void);					// 全部停止
void PauseSound( void );				// 一時停止
void ResumeSound( void );				// 再開

void SetVolume(float fVol);				// 音量調整

#endif
