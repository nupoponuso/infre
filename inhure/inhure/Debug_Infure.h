#pragma once

#include <string>

//�O���錾
namespace F_lib_Fremworker
{
	class SceneBase;
}
namespace F_lib_Render
{
	class D2DTextParams;
}

// �f�o�b�O�p
// �t�@���N�V�����L�[�ŃV�[���`�F���W�ł���
void DebugSceneChange(F_lib_Fremworker::SceneBase* scene);
// ��1�����̃V�[�����̂�\������
void DebugSceneString(std::string str, F_lib_Render::D2DTextParams* text);
// �����ꂽ�L�[�{�[�h�̃{�^������ʍ���ɕ\������
// Note�F��Ŏ�������
