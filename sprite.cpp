#include "sprite.h"

Sprite::Sprite(QString appearance, int spd): speed(spd){
	changeAppearance(appearance);
}


void Sprite::move(const Tile level[][LEVEL_WIDTH]){
	curdir = nextdir;
	this->setPos(this->x() + speed * curdir.x, this->y() + speed * curdir.y);
}

void Sprite::setNextDir(int x, int y){
	nextdir = Vec(x,y);
}

void Sprite::changeAppearance(QString img){
	setPixmap(QPixmap(img));
}
