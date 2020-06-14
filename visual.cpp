#include "visual.h"
#include "constants.h"

Visual::Visual(): QObject(), QGraphicsPixmapItem(){

}


Vec Visual::getScreenPos(int i, int j){
	return Vec(j*TILE_WIDTH, i*TILE_HEIGHT);
}

Vec Visual::getScreenPos(Idx v){
	return getScreenPos(v.i, v.j);
}
