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
	CreateTextureFromFile(Device, L"data/t/UI¼.png", &tex);
	list.push_back(tex);

>>>>>>> D2Dæ©è½å°å¥ãåã³ã«ã¹ã¿ã ã¤ã³ãããéçºéå§
	return E_NOTIMPL;
}
