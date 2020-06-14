#ifndef IDX_H
#define IDX_H


class Idx  //simple container, like Vec, but for indices
{
public:
	int i,j;
	Idx(int i = 0, int j = 0): i(i), j(j){};
	Idx(const Idx &v): i(v.i), j(v.j){};
};

#endif // IDX_H
