#include "controllerrandom.h"

ControllerRandom::ControllerRandom(Level *level, Ghost *ghost, Pacman *pacman):
	GhostController(level, ghost, pacman)
{

}

void ControllerRandom::findTarget(){
	int x = rng.bounded(0,level->getWidth() - 1);
	int y = rng.bounded(0,level->getHeight() -1);

	target = Vec(x,y);
}

