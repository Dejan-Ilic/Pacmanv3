#ifndef LEVEL_H
#define LEVEL_H
#include "gameItems/tile.h"
#include "util/idx.h"
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
	bool isCorrectlyLoaded() const;
	bool isCorrectlySaved() const;
	Idx getSpawn() const;
	int getWidth() const;
	int getHeight() const;

	Idx getGhostSpawn(int i);

	bool eatCoin(int i, int j);
	bool eatCoin(Idx v);

	QString saveLevel();


private:
	Tile *tiles;
	Tile emptytile; //the "out of bounds" tile

	QString levelname;
	int width, height;
	bool correctly_loaded = false;
	bool correctly_saved = false;
	enum DrawMode drawmode;
	QGraphicsScene *scene;

	Idx spawnlocation;
	Idx ghostspawns[4];
	int numcoins = 0;

	Tile& getTile(int i, int j);
	void initTile(int i, int j, enum Type t);
	bool loadLevel();


};

#endif // LEVEL_H
