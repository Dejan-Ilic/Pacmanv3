#ifndef SPRITE_H
#define SPRITE_H

#include "visual.h"
#include "tile.h"
#include "direction.h"
#include "constants.h"
#include "level.h"


class Sprite : public Visual{
public:
	Sprite(QString appearance, int speed);
	void move(const Level *level);
	void changeAppearance(QString img);
	void setNextDir(Direction);
	void setSpeed(int s);
	void setCanPassGate(bool b);

	void setPos_ij(int i, int j) override;
	void setPos_ij(Idx v) override;

protected:
	int speed;
	Direction curdir = DOWN;
	Direction nextdir = DOWN;
	bool canPassGate = false;
};

#endif // SPRITE_H
