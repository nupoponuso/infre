#include "Text.h"
#include "Window.h"

#pragma warning(suppress : 4996)

namespace F_lib_Render
{

	//
	Text::Text()
	{
		Position = XMFLOAT2(0, 0);
		alpa = 1.0f;
		ref.right = 800;
		fontid = 0;


	}


	//
	void Text::init(HWND _hWnd, RenderingEngine * _engine)
	{
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2DFactory);
		_engine->getSwapChain()->GetBuffer(0, IID_PPV_ARGS(&DXGISurface));

		FLOAT dpiX, dpiY;
		D2DFactory->GetDesktopDpi(&dpiX, &dpiY);

		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

		D2DFactory->CreateDxgiSurfaceRenderTarget(DXGISurface, &props, &RnderTerget);

		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown * *>(&DWriteFactory));

		initdata_textfont dat;
		CreateTextFormat(dat);
		
		RnderTerget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &SolidBrush);

		HDC hdc = GetDC(_hWnd);
		TEXTMETRIC tm;
		GetTextMetrics(hdc, &tm);
		size = tm.tmHeight;

	}

	void Text::CreateTextFormat(initdata_textfont _dat)
	{
		IDWriteTextFormat* font;

		DWriteFactory->CreateTextFormat(_dat.name.c_str(), nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, _dat._size, L"", &font);
		font->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

		fontlist.push_back(font);

	}


	//
	void Text::draw(std::wstring _text)
	{
		textdat dat;
		text = _text;

		if (alpa != 1.0f)dat.alpa = alpa;
		if (fontid != 0) dat.id = fontid;
		dat.ref = D2D1::RectF(Position.x, Position.y, ref.right, Position.y + fontlist[fontid]->GetFontSize());
		dat.text = text;

		list.push_back(dat);

	}


	//
	void Text::render()
	{
		
		RnderTerget->BeginDraw();

		for (auto dat : list)
		{
			ref = dat.ref;
			SolidBrush->SetOpacity(dat.alpa);
			
			if (dat.id != fontid)
				fontid = dat.id;
			
			RnderTerget->DrawText(dat.text.c_str(), dat.text.size(), fontlist[fontid], ref, SolidBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);

		}

		RnderTerget->EndDraw();

		list.clear();

	}


	//
	void Text::setfont(int _id)
	{
		fontid = _id;

	}

	
}