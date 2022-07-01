#pragma once

#include "Mover2D.h"

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


class Obstacle : public Mover2D
{
public:
	Obstacle(initObstacledata);

	void Update() {}
	void Draw();

};
