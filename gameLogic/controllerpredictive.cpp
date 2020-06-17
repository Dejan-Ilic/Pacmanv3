#include "controllerpredictive.h"

ControllerPredictive::ControllerPredictive(Level *level, Ghost *ghost, Pacman *pacman):
	GhostController(level, ghost, pacman)
{

}

void ControllerPredictive::findTarget(){
	int dx = 0, dy=0;
	setDirection(dx,dy, pacman->getCurDir());

	target = pacman->getCenterPos() + Vec(TILE_WIDTH*4*dx, TILE_HEIGHT*4*dy);
}
