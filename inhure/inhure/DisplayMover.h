#pragma once

#include "Mover2D.h"
//#include "MoverList.h"
//#include "F_lib/include/Mesh_Fbxmodel.h"

//‘O•ûéŒ¾
namespace F_lib_Render
{
	class Mesh_Fbx;
	class D2DTextParams;
}

struct initdisplaydata
{
	F_lib_Fremworker::ResourceManager* R;
	XMFLOAT3 pos;
	int modelId;
};

class DisplayMover : public Mover2D
{
public:
	DisplayMover(initdisplaydata);
	~DisplayMover();

	void terhit(Mover2D*);
	void herhit(Mover2D*);

	F_lib_Mover::Colision_2D* getcol() override;

	void update();
	void Draw();

private:
	F_lib_Render::Mesh_Fbx* mesh;
	F_lib_Render::D2DTextParams* text;

};

