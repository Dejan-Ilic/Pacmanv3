#include "sprite.h"
#include "constants.h"

Sprite::Sprite(QString appearance, int spd): speed(spd){
	changeAppearance(appearance);
	setTransformOriginPoint(SPRITE_WIDTH/2, SPRITE_HEIGHT/2);
}


void Sprite::move(const Level *level){
	curdir = nextdir;
	this->setPos(this->x() + speed * curdir.x, this->y() + speed * curdir.y);
}

void Sprite::setNextDir(int x, int y){
	nextdir = Vec(x,y);
}

Vec Sprite::getScreenPos(int i, int j){
	return Vec(j*TILE_WIDTH - TILE_WIDTH/2, i*TILE_HEIGHT - TILE_HEIGHT/2);
}

Vec Sprite::getScreenPos(Idx v){
	return Sprite::getScreenPos(v.i, v.j);
}

void Sprite::setPos_ij(int i, int j){
	Vec v = getScreenPos(i,j);
	this->setPos(v.x, v.y);
}

void Sprite::setPos_ij(Idx v){
	setPos_ij(v.i, v.j);
}

void Sprite::changeAppearance(QString img){
	setPixmap(QPixmap(img));
}
