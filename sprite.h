#ifndef SPRITE_H
#define SPRITE_H

#include "visual.h"
#include "tile.h"
#include "vec.h"
#include "constants.h"
#include "level.h"


class Sprite : public Visual{
public:
	Sprite(QString appearance, int speed);
	void move(const Level *level);
	void changeAppearance(QString img);
	void setNextDir(int x, int y);
	void setSpeed(int s);

	void setPos_ij(int i, int j) override;
	void setPos_ij(Idx v) override;

protected:
	int speed;
	Vec curdir;
	Vec nextdir;
	bool canPassGate = false;
};

#endif // SPRITE_H
