#include "visual.h"
#include "util/constants.h"

#include <math.h>

Visual::Visual(): QObject(), QGraphicsPixmapItem(){

}


Vec Visual::idxToVec(int i, int j){
	return Vec(j*TILE_WIDTH, i*TILE_HEIGHT);
}

Vec Visual::idxToVec(Idx v){
	return idxToVec(v.i, v.j);
}

Vec Visual::idxToCenteredVec(int i, int j){
	return idxToVec(i, j) + Vec(TILE_WIDTH/2, TILE_HEIGHT/2);
}

Vec Visual::idxToCenteredVec(Idx v){
	return idxToCenteredVec(v.i, v.j);
}

Idx Visual::vecToIdx(int x, int y){
	int i = floor((y)/static_cast<double>(TILE_HEIGHT) + 0.5);
	int j = floor((x)/static_cast<double>(TILE_WIDTH) + 0.5);

	return Idx(i,j);
}

Idx Visual::vecToIdx(Vec v){
	return vecToIdx(v.x, v.y);
}

Idx Visual::centeredVecToIdx(Vec v){
	return vecToIdx(v.x - TILE_WIDTH/2, v.y - TILE_HEIGHT/2);
}

Idx Visual::centeredVecToIdx(int x, int y){
	return centeredVecToIdx(Vec(x,y));
}

Idx Visual::getIdx() const{
	return vecToIdx(x(), y());
}
