#include "TM.h"
#include "F_lib/include/texture.h"


using namespace F_lib_Render;


HRESULT TexM::loadTex()
{

	ID3D11ShaderResourceView* tex;

	CreateTextureFromFile(Device, L"data/t/UI‰¼.png", &tex);
	list.push_back(tex);



	return E_NOTIMPL;
}
