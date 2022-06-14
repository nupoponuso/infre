#pragma once

#include "F_lib/include/ResourceManager.h"
#include "F_lib/include/Mesh_Sprite.h"


//�@UI�N���X
//�@�Q�[������UI�̊��N���X
class UI
{
public:
	UI(F_lib_Fremworker::ResourceManager* _R);

	virtual void Update() = 0;
	virtual void Draw() = 0;

private:
	F_lib_Fremworker::ResourceManager* R;	//���\�[�X
	F_lib_Render::Mesh_Sprite* s;			//�X�v���C�g

};

