#include "controllerrandom.h"

ControllerRandom::ControllerRandom(){

}

ControllerRandom::~ControllerRandom(){

}

void ControllerRandom::findTarget(Level *level, Pacman *pacman){
	int x = rng.bounded(0,level->getWidth());
	int y = rng.bounded(0,level->getHeight());

	target = Vec(x,y);
}

