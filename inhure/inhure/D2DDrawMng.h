#pragma once

#include <vector>

// ëOï˚êÈåæ
namespace F_lib_Render
{
	class D2DText;
	class D2DFucnComponent;
}
namespace F_lib_Render
{
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