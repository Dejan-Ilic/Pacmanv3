#include "controlleraggressive.h"

ControllerAggressive::ControllerAggressive(Level *level, Ghost *ghost, Pacman *pacman):
	GhostController(level, ghost, pacman)
{

}

void ControllerAggressive::findTarget(){
	target = pacman->getCenterPos();
}
