#include "UIPlayer.h"

#include "Player.h"
#include "RM.h"
#include "F_lib/include/Mesh_Sprite.h"

#define TEXTPOSVALX (60)
#define TEXTPOSVALY (30)

UIPlayer::UIPlayer(F_lib_Fremworker::ResourceManager *_R, Player *_p)
	:UI(_R), p(_p)
{
	Text = _R->meshM->getText();
	Textrue = _R->TM->gettex(0);
}

void UIPlayer::Update()
{
}

void UIPlayer::Draw()
{

	s->reset();
	s->setSize(1280, 800);
	s->setTexture(Textrue);
	s->RDraw(true);

	textpos.x = 100;
	textpos.y = 460;
	Text->setPosition(textpos);
	string = L"hp :";
	Text->draw(string);
	
	textpos.x += TEXTPOSVALX;
	Text->setPosition(textpos);
	string = std::to_wstring(p->getStetas().hp);
	Text->draw(string);
	
	textpos.x = 100;
	textpos.y += TEXTPOSVALY;
	Text->setPosition(textpos);
	string = L"経験値:";
	Text->draw(string);
	
	textpos.x += TEXTPOSVALX;
	Text->setPosition(textpos);
	string = std::to_wstring(p->getStetas().ep);
	Text->draw(string);

	textpos.x = 100;
	textpos.y += TEXTPOSVALY;
	Text->setPosition(textpos);
	string = L"最大経験値:";
	Text->draw(string);
	
	textpos.x += TEXTPOSVALX;
	Text->setPosition(textpos);
	string = std::to_wstring(p->getStetas().epMax);
	Text->draw(string);

	textpos.x = 100;
	textpos.y += TEXTPOSVALY;
	Text->setPosition(textpos);
	string = L"level:";
	Text->draw(string);
	
	textpos.x += TEXTPOSVALX;
	Text->setPosition(textpos);
	string = std::to_wstring(p->getStetas().level);
	Text->draw(string);

}
