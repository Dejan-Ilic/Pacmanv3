#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>
#include <QObject>

#include "vec.h"
#include "idx.h"


enum Type{
	empty,
	wall,
	ghost_gate,
	ghost_floor,
	teleportA,
	teleportB,
	fruit,
	coin,
	pill,
	spawn,
	error
};

class Tile: public QObject, public QGraphicsPixmapItem{
public:
	Tile(enum Type t=empty);
	Tile(const Tile &t);

	enum Type getType() const;
	void setType(enum Type t);

	//statics
	static char encode(enum Type t);
	static enum Type decode(char c);
	static QString getImage(enum Type t);

	static Vec getScreenPos(int i, int j);
	static Vec getScreenPos(Idx v);
	void setPos_ij(int i, int j);
	void setPos_ij(Idx v);
private:
	enum Type type;


};

#endif // TILE_H
