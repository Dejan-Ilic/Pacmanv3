#include "ghost.h"
#include "gameLogic/ghostcontroller.h"

Ghost::Ghost(QString appearance, int speed, Idx spawn, GhostController *controller):
	Sprite(appearance, speed), appearance(appearance), controller(controller){

	controller->setGhost(this);

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
