#include "idx.h"

Idx::Idx(Direction d){
	setDirection(j, i, d);
}

Idx Idx::operator+(const Idx &v) const{
	return Idx(i + v.i, j + v.j);
}

bool Idx::operator==(const Idx &v) const{
	return i == v.i && j == v.j;
}

bool Idx::operator!=(const Idx &v) const{
	return !(*this == v);
}
