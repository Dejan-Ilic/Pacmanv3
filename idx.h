#ifndef IDX_H
#define IDX_H

#include "direction.h"

class Idx  //simple container, like Vec, but for indices
{
public:
	int i,j;
	Idx(int i = 0, int j = 0): i(i), j(j){};
	Idx(const Idx &v): i(v.i), j(v.j){};
	Idx(Direction d);
};

#endif // IDX_H
