#include "controllerpursuit.h"

ControllerPursuit::ControllerPursuit(Ghost *g): GhostController(g){

}

ControllerPursuit::~ControllerPursuit(){

}

void ControllerPursuit::findTarget(Level *level, Pacman *pacman){
	int dx = 0, dy=0;
	setDirection(dx,dy, pacman->getCurDir());

	target = pacman->getCenterPos() + Vec(-TILE_WIDTH*4*dx, -TILE_HEIGHT*4*dy);
}
