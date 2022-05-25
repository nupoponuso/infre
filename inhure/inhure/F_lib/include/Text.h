#pragma once

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#include "comon.h"

#include <DirectXColors.h>
#include <d2d1.h>
#include <dwrite.h>
#include "RenderingEngine.h"
#include <vector>

struct textdat
{
	std::wstring text;
	D2D1_RECT_F ref;
	float alpa;
	int id;

	textdat()
	{
		alpa = 1.0f;
		id = 0;

	}

};

namespace F_lib_Render
{

	struct initdata_textfont
	{
		std::wstring name;
		float _size;

		initdata_textfont() 
		{
			name = L"ÉÅÉCÉäÉI";
			_size = 10;

		}

	};

	class Text
	{
	public:
		Text();
		void init(HWND _hWnd,RenderingEngine * _engine);
		void CreateTextFormat(initdata_textfont);
		void draw(std::wstring);
		void render();

		void setalpa(float _a) { alpa = _a; }
		void setPosition(XMFLOAT2 _pos) { Position = _pos; }
		void setfont(int);
		
	private:
		ID2D1Factory* D2DFactory;
		IDWriteFactory* DWriteFactory;
		IDWriteTextFormat* TextFormat;
		ID2D1RenderTarget* RnderTerget;
		ID2D1SolidColorBrush* SolidBrush;
		IDXGISurface* DXGISurface;
		D2D1_RECT_F ref;

		std::wstring text;
		XMFLOAT2 Position;

		float alpa, size;
		int fontid;

		std::vector<textdat> list;
		std::vector<IDWriteTextFormat*> fontlist;

	};

}
