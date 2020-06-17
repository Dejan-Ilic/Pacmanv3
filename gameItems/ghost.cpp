#include "ghost.h"

Ghost::Ghost(QString appearance, int speed, Idx spawn):
	Sprite(appearance, speed), spawn(spawn), appearance(appearance){

	canPassGate = true;

	setPos_ij(spawn);

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

void Ghost::toSpawn(){
	setPos_ij(spawn);
}
