#pragma once

#include <vector>
#include <DirectXColors.h>
#include <d2d1.h>
#include <dwrite.h>

#include "D2DText.h"
#include "D2DFunctions.h"

// libéwíË
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")


namespace F_lib_Render
{
	// ëOï˚êÈåæ
	class D2DText;
	//class D2DFuncComponent;

	class D2DTextMng
	{
	public:
		D2DTextMng();
		~D2DTextMng();

		void Add(D2DText* text);
		void Remove(D2DText* text);
		void RemoveAll();
		void Render();

	private:
		std::vector<D2DText*> List;
	};

	//class D2DFuncMng
	//{
	//public:
	//	D2DFuncMng();
	//	~D2DFuncMng();

	//	void Add(D2DFuncComponent* comp);
	//	void Remove(D2DFuncComponent* comp);
	//	void RemoveAll();
	//	void Render();

	//private:
	//	std::vector<D2DFuncComponent*> List;
	//};

}