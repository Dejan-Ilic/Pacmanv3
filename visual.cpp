#include "visual.h"
#include "constants.h"

Visual::Visual(): QObject(), QGraphicsPixmapItem(){

}


Vec Visual::getScreenPos(int i, int j){
	return Vec(j*TILE_WIDTH + TILE_WIDTH/2, i*TILE_HEIGHT + TILE_HEIGHT/2);
}

Vec Visual::getScreenPos(Idx v){
	return getScreenPos(v.i, v.j);
}
