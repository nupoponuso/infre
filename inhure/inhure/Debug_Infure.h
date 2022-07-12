#pragma once

#include <string>

//前方宣言
namespace F_lib_Fremworker
{
	class SceneBase;
}
namespace F_lib_Render
{
	class D2DTextParams;
}

// デバッグ用
// ファンクションキーでシーンチェンジできる
void DebugSceneChange(F_lib_Fremworker::SceneBase* scene);
// 第1引数のシーン名称を表示する
void DebugSceneString(std::string str, F_lib_Render::D2DTextParams* text);
// 押されたキーボードのボタンを画面左上に表示する
// Note：後で実装する
