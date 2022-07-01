//-------------------------------------------
//
//		meshmanegerクラス | meshmaneger.cpp |
//		auhor: hujioka tomoya
//		
//-------------------------------------------

#pragma once

//インクルード
#include "datemaneger.h"
#include <vector>
#include "Mesh_Fbxmodel.h"
#include "Mesh_billbord.h"
#include "Text.h"


namespace F_lib_Fremworker
{
	
	//MeshManegerクラス　継承->dateManeger
	//クラスメンバ
	class MeshManeger : public dateManeger
	{
	public:
		MeshManeger(F_lib_Render::RenderingEngine*);

		virtual void detaLode(int _deta) = 0;
		
		F_lib_Render::Mesh_Sprite*   getSprite()   { return Sprite; }
		F_lib_Render::Mesh_billbord* getBillbord() { return Billbord; }
		F_lib_Render::Mesh_Fbx*	     getModel(int i) { return fbxlist[i]; }
		F_lib_Render::Camera*        getCamera()   { return c; }
		F_lib_Render::Light_Point*   getLight()    { return l; }
		F_lib_Render::Text*          getText()	   { return text; }

	protected:
		F_lib_Render::RenderingEngine* Engine;
		std::vector<F_lib_Render::Mesh_Fbx*> fbxlist;
		F_lib_Render::Mesh_Sprite* Sprite;
		F_lib_Render::Mesh_billbord* Billbord;
		F_lib_Render::Camera* c;
		F_lib_Render::Light_Point* l;
		F_lib_Render::Text* text;
		F_lib_Render::Mesh_ShaderDat* shder2D, *shder3D, *shder3DB;

	};

}