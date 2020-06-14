#ifndef VEC_H
#define VEC_H

#include "direction.h"

class Vec //very simple container
{
public:
	int x,y;
	Vec(int x = 0, int y = 0): x(x), y(y){};
	Vec(const Vec &v): x(v.x), y(v.y){};
	Vec(enum Direction d);
};

#endif // VEC_H
