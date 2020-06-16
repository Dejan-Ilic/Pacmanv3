#include "idx.h"

Idx::Idx(Direction d){
	setDirection(j, i, d);
}

Idx Idx::operator+(const Idx &v){
	return Idx(i + v.i, j + v.j);
}

bool Idx::operator==(const Idx &v){
	return i == v.i && j == v.j;
}

bool Idx::operator!=(const Idx &v){
	return !(*this == v);
}
