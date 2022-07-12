#include "DisplayMover.h"

#include <sstream>

#include "input.h"
#include "F_lib/include/Mesh_Fbxmodel.h"
#include "RM.h"
#include "D2DText.h"

using namespace F_lib_Render;

DisplayMover::DisplayMover(initdisplaydata _dat)
	: Mover2D(_dat.R)
	, editable(false)
	, setType(-1)
{
	//‰Šú‰»
	Position = _dat.pos;
	mesh = _dat.R->meshM->getModel(_dat.modelId);
	mesh->setPosition(Position);
	mesh->setangle(Angle);
	mesh->setSize(_dat.size);


	//•¶Žš•\Ž¦—p
	XMFLOAT3 pos = mesh->getPosition();
	XMFLOAT3 angle = mesh->getangle();
	XMFLOAT3 size =  mesh->getsize();
	std::stringstream ss;
	ss << "pos : " << pos.x << "," << pos.y << "," << pos.z << std::string("\n")
		<< "angle : " << angle.x << "," << angle.y << "," << angle.z << std::string("\n")
		<< "size : " << size.x << "," << size.y << "," << size.z << std::string("\n");

	TextData td;
	td.Str = ss.str();
	td.Rect = { -50, -50, 100, 100 };
	td.Pos = { 0, 200 };
	td.Form = TextData::FORM::Point;
	text = new D2DTextParams();
	text->SetData(&td);

}

DisplayMover::~DisplayMover()
{
	//delete text;
}

void DisplayMover::terhit(Mover2D *)
{
}

void DisplayMover::herhit(Mover2D *)
{
}

F_lib_Mover::Colision_2D * DisplayMover::getcol()
{
	return nullptr;
}

void DisplayMover::Update()
{
	if (editable) {
		switch (setType) {
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		default:
			break;
		}
	} else {
		setType = -1;
	}
}

void DisplayMover::Draw()
{
	mesh->RDraw();
}

void DisplayMover::SetPos(XMFLOAT3 pos)
{
	mesh->setPosition(pos);
}

void DisplayMover::SetAngle(XMFLOAT3 angle)
{
	mesh->setangle(angle);
}

void DisplayMover::SetSize(XMFLOAT3 size)
{
	mesh->setSize(size);
}

void DisplayMover::SetEdit(bool enable)
{
	editable = enable;
}
