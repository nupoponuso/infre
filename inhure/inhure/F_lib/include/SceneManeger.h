//--------------------------
//
//		�V�[���p�N���X�@�V�[���̊Ǘ��Ɏg���@| Entitymen.cpp |
//
//		Scnen_Base�N���X�@SceneManeger�N���X
//		auhor: hujioka tomoya
//		
//--------------------

#pragma once

//�C���N���[�h
#include "comon.h"
//#include "singlton.h"
#include "ResourceManager.h"
#include "RenderingEngine.h"
#include "paramerter.h"




namespace F_lib_Fremworker
{

	//�V�[���p
	enum  Scene_type
	{
		Scene_title = 0,	//�^�C�g��
		Scene_game,
		Scene_book,

		Scene_Num			//�ԕ�
	};


	// SceneBase�N���X�@--------------
	// �p���p���z�N���X

	class SceneBase
	{
	public:
		SceneBase(F_lib_Fremworker::ResourceManager* _ResouseManeger, bool _usefade = false);
		virtual ~SceneBase() {};

		virtual void update() = 0;
		virtual void Draw() = 0;

		void updetedade();
		void Drawfede();

		void setfadein();

		Scene_type getnextscene() { return next; }
		HRESULT	   gethr() { return hr; }

		bool getfade() { return usefade; }
		bool getfadein() { return fadein; }

	protected:
		HRESULT	hr;

		F_lib_Fremworker::ResourceManager* Resource;
		F_lib_Render::Mesh_Sprite* s;
		ID3D11ShaderResourceView* Texture;
		Scene_type next;

		XMFLOAT2 spos;
		XMFLOAT3 fadecolor;
		int framecount;
		float textalph, fadealph[2], addfadealph;
		bool  usefade, fadein, countflame;

	};

	//---------------------


	//  SceneManeger�N���X�@--------------
	//�V�[���Ǘ��p�N���X�@�V���O���g���p�^�[�����g�p

	class SceneManeger 
	{
	public:
		SceneManeger();
		~SceneManeger();

		void updateScene();
		void DrawScene();
		void DrawLoad();
		virtual void strtSceneChange(Scene_type next) = 0;

	protected:

		bool Drawload, isload;
		F_lib_Fremworker::SceneBase* Scene;
		F_lib_Fremworker::ResourceManager* Resource;
		ID3D11ShaderResourceView* Texture;
		F_lib_Render::Mesh_Sprite* s;

	};

	//--------------

}