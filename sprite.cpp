#include "sprite.h"
#include "constants.h"

#include <stdlib.h>

#include <qDebug>

Sprite::Sprite(QString appearance, int spd): speed(spd){
	changeAppearance(appearance);
	setTransformOriginPoint(SPRITE_WIDTH/2, SPRITE_HEIGHT/2);
}


void Sprite::move(const Level *level){
	int x = getCenterX();
	int y = getCenterY();
	Idx curidx = getIdx(); //currrent square
	Idx nextidx = curidx + Idx(curdir); //next square if no turns are made
	Idx wantedidx = curidx + Idx(nextdir); //next turn

	Vec cursquare = Visual::getCenteredScreenPos(curidx);
	//Vec nextsquare = Visual::getCenteredScreenPos(nextidx);
	Vec wantedsquare = Visual::getCenteredScreenPos(wantedidx);

	enum Type nexttype = level->getType(nextidx);
	enum Type wantedtype = level->getType(wantedidx);

	bool passNext =	  ((nexttype != wall)	&&	(nexttype != ghost_gate   || canPassGate));
	bool passWanted = ((wantedtype != wall) &&	(wantedtype != ghost_gate || canPassGate));

	//qDebug() << cursquare.x << ", " << cursquare.y << " | " << x << ", " << y;

	if(abs(curidx.i) == abs(nextidx.i) && abs(curidx.j) == abs(nextidx.j) && curidx.i != nextidx.i && curidx.j != nextidx.j){
		//zelfde richting, tegenovergestelde zin
		curdir = nextdir;
		setRotation(getPacmanRotation(curdir));


	}else if(passWanted && curdir != nextdir  && (abs(wantedsquare.x - x) <= speed || abs(wantedsquare.y - y) <= speed)){
		//take the turn
		this->setPos_ij(curidx.i, curidx.j);
		curdir = nextdir;
		setRotation(getPacmanRotation(curdir));


	}else if(!passNext  && cursquare.l1dist(Vec(x, y)) <= speed){
		//stop just before wall, perfectly in the center
		this->setPos_ij(curidx.i, curidx.j);


	}else{
		//just move forward
		Vec dir = Vec(curdir);
		this->setPos(this->x() + speed * dir.x, this->y() + speed * dir.y);
	}


}

void Sprite::setNextDir(Direction d){
	nextdir = d;
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

int Sprite::getCenterX() const {
	return x() + SPRITE_WIDTH/2;
}
int Sprite::getCenterY() const{
	return y() + SPRITE_HEIGHT/2;
}

Vec Sprite::getCenterPos() const{
	return Vec(getCenterX(), getCenterY());
}


void Sprite::changeAppearance(QString img){
	setPixmap(QPixmap(img));
}
