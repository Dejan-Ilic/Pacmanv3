#ifndef LEVEL_H
#define LEVEL_H
#include "tile.h"
#include "idx.h"
#include <QGraphicsScene>

enum DrawMode{
	DRAWMODE_GAME,
	DRAWMODE_EDITOR
};

class Level{
public:
	Level(QString levelname, enum DrawMode drawmode, QGraphicsScene *scene);
	~Level();

	enum Type getType(int i, int j) const;
	enum Type getType(const Idx &v) const;
	void setType(int i, int j, enum Type t);
	bool isLoadedCorrectly() const;
	Idx getSpawn() const;
	int getWidth() const;
	int getHeight() const;


private:
	Tile *tiles;
	Tile emptytile; //the "out of bounds" tile

	int width, height;
	bool correctly_loaded;
	enum DrawMode drawmode;

	Idx spawnlocation;

	Tile& getTile(int i, int j);


};

#endif // LEVEL_H
