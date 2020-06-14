#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsRectItem>
#include "tile.h"
#include "vec.h"
#include "constants.h"


class Sprite : public QObject, public QGraphicsPixmapItem{
	Q_OBJECT
public:
	Sprite(QString appearance, int speed);
	void move(const Tile level[][LEVEL_WIDTH]);
	void changeAppearance(QString img);
	void setNextDir(int x, int y);

private:
	int speed;
	Vec curdir;
	Vec nextdir;
};

#endif // SPRITE_H
