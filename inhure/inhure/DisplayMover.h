#pragma once

#include "Mover2D.h"
//#include "MoverList.h"
//#include "F_lib/include/Mesh_Fbxmodel.h"

//ëOï˚êÈåæ
namespace F_lib_Render
{
	class Mesh_Fbx;
	class D2DTextParams;
	class Mesh_billbord;
}

struct initdisplaydata
{
	F_lib_Fremworker::ResourceManager* R;
	XMFLOAT3 pos;
	float size;
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

	void Update();
	void Draw();
	void SetPos(XMFLOAT3 pos);
	void SetAngle(XMFLOAT3 angle);
	void SetSize(XMFLOAT3 size);
	void SetEdit(bool enable);

private:
	F_lib_Render::Mesh_Fbx* mesh;
	F_lib_Render::Mesh_billbord* board;
	F_lib_Render::D2DTextParams* text;
	bool editable;
	int setType;
};

