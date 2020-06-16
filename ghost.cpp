#include "ghost.h"

Ghost::Ghost(QString appearance, int speed, Idx spawn):
	Sprite(appearance, speed), spawn(spawn){

	canPassGate = true;

	setPos_ij(spawn);

}


bool Ghost::isAlive(){
	return alive;
}

bool Ghost::isScared(){
	return scared;
}

void Ghost::setScared(int time){
	scared = true;
	//todo
}
