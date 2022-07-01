#include "TM.h"
#include "F_lib/include/texture.h"


using namespace F_lib_Render;


HRESULT TexM::loadTex()
{

	ID3D11ShaderResourceView* tex;

	CreateTextureFromFile(Device, L"data/t/EXMemory.png", &tex);
	list.push_back(tex);

	CreateTextureFromFile(Device, L"data/t/EXMemory.png", &tex);
	list.push_back(tex);

	CreateTextureFromFile(Device, L"data/t/EXBar.png", &tex);
	list.push_back(tex);

	CreateTextureFromFile(Device, L"data/t/EXBar.png", &tex);
	list.push_back(tex);


=======
	//0
	CreateTextureFromFile(Device, L"data/t/EXBar.png", &tex);
	list.push_back(tex);

	//1
	CreateTextureFromFile(Device, L"data/t/EXMemory.png", &tex);
	list.push_back(tex);

	//2
	CreateTextureFromFile(Device, L"data/t/HPBar.png", &tex);
	list.push_back(tex);

	//3
	CreateTextureFromFile(Device, L"data/t/HPMemory.png", &tex);
	list.push_back(tex);

	//4
	CreateTextureFromFile(Device, L"data/t/UI��.png", &tex);
	list.push_back(tex);

>>>>>>> D2D機能導入、及びカスタムインプット開発開始
	return E_NOTIMPL;
}
