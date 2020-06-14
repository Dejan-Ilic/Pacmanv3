#ifndef VEC_H
#define VEC_H


class Vec
{
public:
	int x,y;
	Vec(int x = 0, int y = 0): x(x), y(y){};
	Vec(const Vec &v): x(v.x), y(v.y){};
};

#endif // VEC_H
