#pragma once

#include "F_lib/include/TextureManeger.h"

class TexM :public F_lib_Fremworker::TextureManeger
{
public:

	TexM(ID3D11Device* _deice) :F_lib_Fremworker::TextureManeger(_deice) {};

	HRESULT loadTex();

};

