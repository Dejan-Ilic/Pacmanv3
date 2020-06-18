#include "controlleraggressive.h"

ControllerAggressive::ControllerAggressive(Ghost *g): GhostController(g){

}

ControllerAggressive::~ControllerAggressive(){

}

void ControllerAggressive::findTarget(Level *level, Pacman *pacman){
	target = pacman->getCenterPos();
}
