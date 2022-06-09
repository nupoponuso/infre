#include "Obstacle.h"



Obstacle::Obstacle(initObstacledata _dat) : Mover(_dat.R, XMFLOAT3(), 0)
{
	myid = mover_Obstacle;
	Position = _dat.pos;

}

void Obstacle::Draw()
{


}
