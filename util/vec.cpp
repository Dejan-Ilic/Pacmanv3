#include "vec.h"
#include <stdlib.h>

Vec::Vec(Direction d){
	setDirection(x, y, d);
}

Vec Vec::operator+(const Vec &v) const{
	return Vec(x + v.x, y + v.y);
}

int Vec::l1dist(const Vec &v) const{
	return abs(x - v.x) + abs(y - v.y);
}
