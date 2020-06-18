#include "ghost.h"
#include "gameLogic/ghostcontroller.h"

#include <gameLogic/controlleraggressive.h>
#include <gameLogic/controllerpredictive.h>
#include <gameLogic/controllerpursuit.h>
#include <gameLogic/controllerrandom.h>

const QString Ghost::baseScaredAppearance = GHOST_SCARED;

Ghost::Ghost(QString appearance, int speed, Idx spawn, ControllerType ct):
	Sprite(appendAppearance(appearance, LEFT), speed), appearance(appearance), baseAppearance(appearance){

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
	default://RANDOM
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
		appearance = baseScaredAppearance;

	}else{
		speed = NORMAL_SPEED;
		appearance = baseAppearance;
	}

	changeAppearance(appendAppearance(appearance, curdir));

}

void Ghost::rotateSprite(){
	changeAppearance(appendAppearance(appearance, curdir));
}

void Ghost::toSpawn(Idx spawn){
	setPos_ij(spawn);
}

void Ghost::move(Level *level, Pacman *pacman){
	controller->plan(level, pacman);
	Sprite::move(level);
}

QString Ghost::appendAppearance(QString app, Direction dir){
	QString s = "";

	switch(dir){
	case LEFT: return app + "_LEFT.png";
	case RIGHT: return app + "_RIGHT.png";
	case UP: return app + "_UP.png";
	case DOWN: return app + "_DOWN.png";
	}
}
