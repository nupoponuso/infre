#pragma once


#include "UI.h"
#include "F_lib/include/Text.h"

class UIPlayer : public UI
{
public:
	UIPlayer(F_lib_Fremworker::ResourceManager*,class Player*);

	void Update();
	void Draw();

private:
	class Player* p;
	F_lib_Render::Text* Text;
	ID3D11ShaderResourceView* Textrue;
	std::wstring string;
	XMFLOAT2 textpos;

};

