#pragma once

#include "F_lib/include/mover.h"

enum Obstacletype
{
	Obstacle_Wall,

	Obstacle_MAX
};

struct initObstacledata
{
	F_lib_Fremworker::ResourceManager* R;
	XMFLOAT3 pos;
	Obstacletype type;

};


class Obstacle : public F_lib_Mover::Mover
{
public:
	Obstacle(initObstacledata);

	void update() {}
	void Draw();

};
