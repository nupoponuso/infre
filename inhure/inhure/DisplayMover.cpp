#include "DisplayMover.h"

#include "F_lib/include/Mesh_Fbxmodel.h"
#include "RM.h"

#include "D2DText.h"
#include <sstream>

using namespace F_lib_Render;

DisplayMover::DisplayMover(initdisplaydata _dat)
	: Mover2D(_dat.R)
{
	//‰Šú‰»
	Position = _dat.pos;
	mesh = _dat.R->meshM->getModel(_dat.modelId);

	//•¶Žš•\Ž¦—p
	XMFLOAT3 pos = mesh->getPosition();
	XMFLOAT3 angle = mesh->getangle();
	XMFLOAT3 size =  mesh->getsize();
	std::stringstream ss;
	ss << "pos : " << pos.x << "," << pos.y << "," << pos.z << std::string("\n")
		<< "angle : " << angle.x << "," << angle.y << "," << angle.z << std::string("\n")
		<< "size : " << size.x << "," << size.y << "," << size.z << std::string("\n");

	getEngine()->getD2DText()->SetOrigin(D2DText::ORIGIN::CENTER);
	getEngine()->getD2DText()->ReverseYAxis(true);

	TextData td;
	td.Str = ss.str();
	td.Rect = { -100, 100, 200, 200 };
	//td.Pos = { pos.x, pos.y+100 };
	text = new D2DTextParams();
	text->SetData(&td);

}

DisplayMover::~DisplayMover()
{
	delete text;
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
}

void DisplayMover::Draw()
{
	mesh->setPosition(Position);
	mesh->setangle(Angle);
	mesh->setSize(0.2f);
	mesh->RDraw();
}
