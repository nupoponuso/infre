#include "MoverList.h"
#include "Mover2D.h"

void MoverList::update()
{
	for (int i=0;i<list.size();i++ /*list*/)
	{
		Mover2D* m = list[i];
		if (m->Alive)
			m->update();

		if(!m->Alive)
		{
			auto iter = std::find(list.begin(), list.end() - 1, m);
			
			if (iter != list.end() - 1)
				std::iter_swap(iter, list.end() - 1);

			delete list.back();
			list.pop_back();
			
		}


	}

}

void MoverList::Draw()
{
	for (Mover2D* m : list)
		if (m->Alive) m->Draw();

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
	
	for (Mover2D* m: list)
	{
		if (m == _is)
			continue;
	
		Col2 = m->getcol();
		if ((Col1 != nullptr&&Col2 != nullptr) && Col2->ishit(Col1))
		{
			m->herhit(_is);
			_is->terhit(m);

			ref = true;
		}
	
	}
	
	return ref;
}
