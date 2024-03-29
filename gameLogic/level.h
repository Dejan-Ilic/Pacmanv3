#ifndef LEVEL_H
#define LEVEL_H
#include "gameItems/tile.h"
#include "util/idx.h"
#include <QGraphicsScene>

class Level{
public:
	Level(QString levelname, enum DrawMode drawmode, QGraphicsScene *scene);
	~Level();

	enum Type getTileType(int i, int j) const;
	enum Type getTileType(const Idx &v) const;
	void setTileType(int i, int j, enum Type t);
	void setTileType(const Idx &v, enum Type t);
	bool isCorrectlyLoaded() const;
	bool isCorrectlySaved() const;
	Idx getSpawn() const;
	int getWidth() const;
	int getHeight() const;
	int getRemainingCoins() const;
	int getTotalCoins() const;

	Idx getGhostSpawn(int i) const;

	enum Type eat(Vec v);
	enum Type eat(int x, int y);

	QString saveLevel();


private:
	Tile *tiles;
	Tile voidsquare; //the "out of bounds" tile

	QString levelname;
	int width, height;
	bool correctly_loaded = false;
	bool correctly_saved = false;
	enum DrawMode drawmode;
	QGraphicsScene *scene;

	Idx spawnlocation;
	Idx ghostspawns[4];
	int numcoins = 0;
	int totalcoins = 0;

	Tile& getTile(int i, int j);
	void initTile(int i, int j, enum Type t);
	bool loadLevel();


};

#endif // LEVEL_H
