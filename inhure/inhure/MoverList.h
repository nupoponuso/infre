#pragma once

#include <vector>

class MoverList
{
public:
	
	void update();
	void Draw();
	
	void listPush(class Mover2D*);
	bool Ishit(class Mover2D*);

	class Mover2D* getlist(int _id) { return list[_id]; } 
	int getlistNum() { return (int)list.size(); }
	
protected:
	std::vector<class Mover2D*> list;

};

