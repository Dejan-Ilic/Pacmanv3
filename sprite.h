#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsRectItem>
#include "tile.h"
#include "vec.h"
#include "constants.h"
#include "level.h"


class Sprite : public QObject, public QGraphicsPixmapItem{
	Q_OBJECT
public:
	Sprite(QString appearance, int speed);
	void move(const Level *level);
	void changeAppearance(QString img);
	void setNextDir(int x, int y);

	static Vec getScreenPos(int i, int j);
	static Vec getScreenPos(Idx v);
	void setPos_ij(int i, int j);
	void setPos_ij(Idx v);

private:
	int speed;
	Vec curdir;
	Vec nextdir;
};

#endif // SPRITE_H
