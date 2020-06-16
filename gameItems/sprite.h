#ifndef SPRITE_H
#define SPRITE_H

#include "visual.h"
#include "tile.h"
#include "util/direction.h"
#include "util/constants.h"
#include "gameLogic/level.h"


class Sprite : public Visual{
public:
	Sprite(QString appearance, int speed);
	void move(const Level *level);
	void changeAppearance(QString img);
	void setNextDir(Direction);
	void setSpeed(int s);
	void setCanPassGate(bool b);

	bool isAlive();
	void setAlive(bool a);

	void setPos_ij(int i, int j) override;
	void setPos_ij(Idx v) override;

	int getCenterX() const override;
	int getCenterY() const override;
	Vec getCenterPos() const override;

protected:
	int speed;
	Direction curdir = LEFT;
	Direction nextdir = LEFT;
	bool canPassGate = false;
	bool alive = true;
};

#endif // SPRITE_H
