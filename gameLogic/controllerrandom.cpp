#include "controllerrandom.h"

ControllerRandom::ControllerRandom(Level *level, Ghost *ghost, Pacman *pacman):
	GhostController(level, ghost, pacman)
{

}

void ControllerRandom::findTarget(){
	int x = rng.bounded(0,level->getWidth());
	int y = rng.bounded(0,level->getHeight());

	target = Vec(x,y);
}

