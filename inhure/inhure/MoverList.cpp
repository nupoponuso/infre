#include "MoverList.h"
#include "Mover2D.h"

void MoverList::update()
{
	for (auto m : list)
	{
		if (!m->Alive)
		{
			auto iter = std::find(list.begin(), list.end(), m);
			if (iter != list.end())
			{
				std::iter_swap(iter, list.end() - 1);
				list.pop_back();

			}

		}
		else m->update();

	}

}

void MoverList::Draw()
{
	for (auto m : list)
		m->Draw();

}

void MoverList::listPush(Mover2D *_m)
{
	list.push_back(_m);
}

bool MoverList::Ishit(Mover2D * _is)
{
	bool ref = false;
	F_lib_Mover::Colision_2D* Col1, *Col2;
	Col1 = _is->getcol();
	
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == _is)
			continue;
	
		Col2 = list[i]->getcol();
		if ((Col1 != nullptr&&Col2 != nullptr) && Col2->ishit(Col1))
		{
			list[i]->herhit(_is);
			_is->terhit(list[i]);

			ref = true;
		}
	
	}
	
	return ref;
}
