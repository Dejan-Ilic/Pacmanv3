#include "controlleraggressive.h"

ControllerAggressive::ControllerAggressive(){

}

ControllerAggressive::~ControllerAggressive(){

}

void ControllerAggressive::findTarget(Level *level, Pacman *pacman){
	target = pacman->getCenterPos();
}
