#include "sprite.h"
#include "util/constants.h"

#include <stdlib.h>

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

	Vec cursquare = Visual::idxToCenteredVec(curidx);
	//Vec nextsquare = Visual::getCenteredScreenPos(nextidx);
	Vec wantedsquare = Visual::idxToCenteredVec(wantedidx);

	enum Type nexttype = level->getType(nextidx);
	enum Type wantedtype = level->getType(wantedidx);

	bool passNext =	  ((nexttype != wall)	&&	(nexttype != ghost_gate   || canPassGate));
	bool passWanted = ((wantedtype != wall) &&	(wantedtype != ghost_gate || canPassGate));

	if(abs(curidx.i) == abs(nextidx.i) && abs(curidx.j) == abs(nextidx.j) && curidx.i != nextidx.i && curidx.j != nextidx.j){
		//zelfde richting, tegenovergestelde zin
		curdir = nextdir;
		rotateSprite();


	}else if(passWanted && curdir != nextdir  && (abs(wantedsquare.x - x) <= speed || abs(wantedsquare.y - y) <= speed)){
		//take the turn
		this->setPos_ij(curidx.i, curidx.j);
		curdir = nextdir;
		rotateSprite();


	}else if(!passNext  && cursquare.l1dist(Vec(x, y)) <= speed){
		//stop just before wall, perfectly in the center
		this->setPos_ij(curidx.i, curidx.j);


	}else{
		//just move forward
		Vec dir = Vec(curdir);
		this->setPos(this->x() + speed * dir.x, this->y() + speed * dir.y);
	}


}

void Sprite::rotateSprite(){
	setRotation(getPacmanRotation(curdir));
}

bool Sprite::isAlive() const{
	return alive;
}

void Sprite::setAlive(bool a){
	alive = a;
}

int Sprite::getSpeed() const{
	return speed;
}

Direction Sprite::getCurDir() const{
	return curdir;
}

Direction Sprite::getNextDir() const{
	return nextdir;
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

bool Sprite::getCanPassGate() const{
	return canPassGate;
}

void Sprite::setPos_ij(int i, int j){
	Vec v = idxToVec(i,j);
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
