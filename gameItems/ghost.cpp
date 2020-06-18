#include "ghost.h"
#include "gameLogic/ghostcontroller.h"

#include <gameLogic/controlleraggressive.h>
#include <gameLogic/controllerpredictive.h>
#include <gameLogic/controllerpursuit.h>
#include <gameLogic/controllerrandom.h>

Ghost::Ghost(QString appearance, int speed, Idx spawn, ControllerType ct):
	Sprite(appearance, speed), appearance(appearance){

	switch(ct){
	case AGGRESSIVE:
		controller = new ControllerAggressive(this);
		break;
	case PREDICTIVE:
		controller = new ControllerPredictive(this);
		break;
	case PURSUIT:
		controller = new ControllerPursuit(this);
		break;
	case RANDOM:
		controller = new ControllerRandom(this);
		break;

	}

	canPassGate = false;
	alive = false;

	setPos_ij(spawn);

}

Ghost::~Ghost(){
	delete controller;
}

bool Ghost::isScared(){
	return scared;
}

void Ghost::setScared(bool newstate){
	if(scared == newstate){
		return;
	}

	scared = newstate;

	if(scared){
		nextdir = opposite(curdir);
		speed = PILL_SPEED;

		//set sprite to scared
		changeAppearance(GHOST_SCARED);


	}else{
		speed = NORMAL_SPEED;
		//set sprite to ghost
		changeAppearance(appearance);
	}
}

void Ghost::toSpawn(Idx spawn){
	setPos_ij(spawn);
}

void Ghost::move(Level *level, Pacman *pacman){
	controller->plan(level, pacman);
	Sprite::move(level);
}
