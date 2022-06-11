#include "Obstacle.h"



Obstacle::Obstacle(initObstacledata _dat) : Mover2D(_dat.R)
{
	Myid = mover_obstacle;
	Position = _dat.pos;

}

void Obstacle::Draw()
{


}
