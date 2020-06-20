#include "controllerpredictive.h"

ControllerPredictive::ControllerPredictive(Ghost *g): GhostController(g){

}

ControllerPredictive::~ControllerPredictive(){

}

void ControllerPredictive::findTarget(Level *level, Pacman *pacman){
	target = pacman->getCenterPos() + TILE_WIDTH*4*Vec(pacman->getCurDir());
}
