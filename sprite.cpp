#include "sprite.h"
#include "constants.h"

Sprite::Sprite(QString appearance, int spd): speed(spd){
	changeAppearance(appearance);
	setTransformOriginPoint(SPRITE_WIDTH/2, SPRITE_HEIGHT/2);
}


void Sprite::move(const Level *level){
	curdir = nextdir;
	Vec dir = Vec(curdir);
	this->setPos(this->x() + speed * dir.x, this->y() + speed * dir.y);
}

void Sprite::setNextDir(Direction d){
	nextdir = d;
	setRotation(getPacmanRotation(d));
}

void Sprite::setSpeed(int s){
	speed = s;
}

void Sprite::setCanPassGate(bool b){
	canPassGate = b;
}

void Sprite::setPos_ij(int i, int j){
	Vec v = getScreenPos(i,j);
	this->setPos(v.x - TILE_WIDTH/2, v.y - TILE_HEIGHT/2);
}

void Sprite::setPos_ij(Idx v){
	setPos_ij(v.i, v.j);
}


void Sprite::changeAppearance(QString img){
	setPixmap(QPixmap(img));
}
