#pragma once

#include "Wepon.h"

class WeponLyzer : public Wepon
{
public:
	WeponLyzer(initWepondata);

	void Draw();

private:
	void move();
	void ThisAtack();


};

