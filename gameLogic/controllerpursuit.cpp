#include "controllerpursuit.h"

ControllerPursuit::ControllerPursuit(Ghost *g): GhostController(g){

}

ControllerPursuit::~ControllerPursuit(){

}

void ControllerPursuit::findTarget(Level *level, Pacman *pacman){
	target = pacman->getCenterPos() - TILE_WIDTH*4* Vec(pacman->getCurDir());
}
