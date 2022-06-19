//--------------------------
//
//		�V�[���p�N���X�@�V�[���̊Ǘ��Ɏg��
//
//		Scnen_Base�N���X SceneManeger�N���X
//		auhor: hujioka tomoya
//
//		
//--------------------


//�C���N���[�h
#include "SceneManeger.h"
#include "ResourceManager.h"
#include "texture.h"
#include "MeshManeger.h"


namespace F_lib_Fremworker
{
	//SceneManeger�N���X-----------------------------------------

	//�R���X�g���N�^
	//PM,parameter,Scene�̏�����
	SceneManeger::SceneManeger() : Drawload(false), isload(false)
	{ }


	//�f�X�g���N�^
	//PM,parameter�̍폜
	SceneManeger::~SceneManeger()
	{
		delete Resource;

	}


	//updateScene�֐�
	//Scene�̍X�V�Ǝ��̃V�[���̃I�[�_�[�̎擾���V�[���ϑJ
	void SceneManeger::updateScene()
	{
		if (!Scene->getfade())
		{
			if (Scene->getnextscene() == Scene_Num)
				Scene->update();
			else
			{
				if (isload) strtSceneChange(Scene->getnextscene());
				else Drawload = true;

			}

		}
		else Scene->updetedade();

	}


	//DrawScene�֐�
	//Scene�̕`��
	void SceneManeger::DrawScene()
	{
		if (!Drawload)
		{
			Scene->Draw();
			if (Scene->getfade() || Scene->getfadein())
				Scene->Drawfede();

		}
		else
		{
			DrawLoad();
			isload = true;

		}

	}


	//DrawLoad�֐�
	//���[�h��ʂ̕`��
	void SceneManeger::DrawLoad()
	{
		s->reset();
		s->setPosition(0, 0);
		s->Draw();

		s->setPosition(480, -350);
		s->setSize(400, 50);
		s->setColor(1, 1, 1);
		s->Draw();

	}

	//-----------------------------------------

	//SceneBase�N���X----------------------------------------

	//�R���X�g���N�^
	//�l�̏�����
	SceneBase::SceneBase(F_lib_Fremworker::ResourceManager * _ResouseManeger, bool _usefade)
		: usefade(_usefade), Resource(_ResouseManeger), s(_ResouseManeger->meshM->getSprite())
	{
		
		next = Scene_Num;
		fadealph[0] = 1.0f;
		fadealph[1] = 0;
		fadein = false;
		addfadealph = -0.01f;
		countflame = false;
		framecount = 0;

		s->reset();

	}


	//updetedade�֐�
	//�t�F�[�h�̍X�V
	void SceneBase::updetedade()
	{
		fadealph[0] += addfadealph;
		//Resource->meshM->getLight()->update();

		if (fadealph[(fadein) ? 1 : 0] <= fadealph[(fadein) ? 0 : 1])
		{
			usefade = false;
			s->reset();

		}

	}


	//Drawfede�֐�
	//�t�F�[�h�̕`��
	void SceneBase::Drawfede()
	{
		s->reset();
		s->setColor(fadecolor);
		s->setPosition(0, 0);
		//s->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		s->setTexture(nullptr);
		s->setalph(fadealph[0]);
		s->Draw();
		s->setalph(1);
		s->setColor(1, 1, 1);

	}


	//setfadein�֐�
	//�t�F�[�h�C���̐ݒ�
	void SceneBase::setfadein()
	{
		fadealph[0] = 0;
		fadealph[1] = 1.1f;
		usefade = fadein = true;
		addfadealph = 0.01f;

	}

	//-----------------------------------------
}