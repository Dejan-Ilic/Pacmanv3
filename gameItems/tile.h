#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>
#include <QObject>

#include "util/vec.h"
#include "util/idx.h"
#include "visual.h"


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

enum DrawMode{
	DRAWMODE_GAME,
	DRAWMODE_EDITOR
};

class Tile: public Visual{
public:
	Tile(enum Type t=empty);
	Tile(const Tile &t);

	enum Type getType() const;
	void setType(enum Type t);

	//statics
	static char encode(enum Type t);
	static enum Type decode(char c);
	static QString getImage(enum Type t);

	static void setDrawMode(enum DrawMode d);

	void setPos_ij(int i, int j) override;
	void setPos_ij(Idx v) override;

	int getCenterX() const override;
	int getCenterY() const override;
	Vec getCenterPos() const override;

private:
	enum Type type;
	static enum DrawMode drawMode;

};

#endif // TILE_H
