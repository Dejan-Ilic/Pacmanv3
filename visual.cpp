#include "visual.h"
#include "constants.h"

#include <math.h>

Visual::Visual(): QObject(), QGraphicsPixmapItem(){

}


Vec Visual::getScreenPos(int i, int j){
	return Vec(j*TILE_WIDTH, i*TILE_HEIGHT);
}

Vec Visual::getScreenPos(Idx v){
	return getScreenPos(v.i, v.j);
}

Vec Visual::getCenteredScreenPos(int i, int j){
	return getScreenPos(i, j) + Vec(TILE_WIDTH/2, TILE_HEIGHT/2);
}

Vec Visual::getCenteredScreenPos(Idx v){
	return getCenteredScreenPos(v.i, v.j);
}




Idx Visual::getIdx(){
	int i = floor((y())/static_cast<double>(TILE_HEIGHT) + 0.5);
	int j = floor((x())/static_cast<double>(TILE_WIDTH) + 0.5);

	return Idx(i,j);
}
