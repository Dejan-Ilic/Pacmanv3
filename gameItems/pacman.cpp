#include "pacman.h"

Pacman::Pacman(QString appearance, int speed): Sprite(appearance, speed){

}

void Pacman::rotateSprite(){
	setRotation(getPacmanRotation(curdir));
}
