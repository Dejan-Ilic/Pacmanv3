#include "vec.h"
#include <stdlib.h>

Vec::Vec(Direction d){
	setDirection(x, y, d);
}

Vec Vec::operator+(const Vec &v) const{
	return Vec(x + v.x, y + v.y);
}

Vec Vec::operator-(const Vec &v) const{
	return Vec(x - v.x, y - v.y);
}

Vec operator*(int lambda, const Vec &v){
	return Vec(v.x * lambda, v.y * lambda);
}

int Vec::l1dist(const Vec &v) const{
	return abs(x - v.x) + abs(y - v.y);
}

int Vec::l2distSquared(const Vec &v) const{
	return (x - v.x) * (x - v.x) + (y - v.y) * (y - v.y);
}
