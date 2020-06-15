#include "tile.h"
#include "constants.h"

Tile::Tile(enum Type t){
	setType(t);
	setTransformOriginPoint(TILE_WIDTH/2, TILE_HEIGHT/2);
}

Tile::Tile(const Tile &t){
	setType(t.getType());
}

enum Type Tile::getType() const{
	return type;
}

void Tile::setType(enum Type t){
	type = t;
	setPixmap(QPixmap(getImage(t)));
}

QString Tile::getImage(enum Type t){
	QString s = "error";
	switch(t){
	case empty: s= "empty"; break;
	case wall: s= "wall"; break;
	case ghost_gate: s= "ghost_gate"; break;
	case ghost_floor: s= "ghost_floor"; break;
	case teleportA: s= "teleportA"; break;
	case teleportB: s= "teleportB"; break;
	case pill: s= "pill"; break;
	case coin: s= "coin"; break;
	case fruit: s= "fruit"; break;
	case spawn: s= "spawn"; break;
	//default: s= "error"; break;
	}

	return ":/images/" + s + ".png";
}

enum Type Tile::decode(char c){
	switch(c){
	case 'e': return empty;
	case 'w': return wall;
	case 'g': return ghost_gate;
	case 'f': return ghost_floor;
	case 'A': return teleportA;
	case 'B': return teleportB;
	case 'p': return pill;
	case 'c': return coin;
	case 's': return spawn;
	}
	return error;
}

char Tile::encode(enum Type t){
	switch(t){
	case empty: return 'e';
	case wall: return 'w';
	case ghost_gate: return 'g';
	case ghost_floor: return 'f';
	case teleportA: return 'A';
	case teleportB: return 'B';
	case pill: return 'p';
	case coin: return 'c';
	case spawn: return 's';
	}
	return 0;
}


void Tile::setPos_ij(int i, int j){
	Vec v = getScreenPos(i,j);
	this->setPos(v.x, v.y);
}

void Tile::setPos_ij(Idx v){
	setPos_ij(v.i, v.j);
}

int Tile::getCenterX() const {
	return x() + TILE_WIDTH/2;
}
int Tile::getCenterY() const{
	return y() + TILE_HEIGHT/2;
}

Vec Tile::getCenterPos() const{
	return Vec(getCenterX(), getCenterY());
}


