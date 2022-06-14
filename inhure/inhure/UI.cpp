#include "UI.h"
#include "MeshM.h"

//　コンストラクタ
//　リソース、スプライトのポインタ確保
UI::UI(F_lib_Fremworker::ResourceManager * _R) :R(_R),s(_R->meshM->getSprite())
{ }
