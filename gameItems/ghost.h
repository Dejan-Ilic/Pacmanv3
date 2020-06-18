#ifndef GHOST_H
#define GHOST_H
#include "pacman.h"
#include "sprite.h"
#include "util/constants.h"

class GhostController;

enum ControllerType{ AGGRESSIVE, PREDICTIVE, PURSUIT, RANDOM};

class Ghost: public Sprite{
public:
	Ghost(QString appearance, int speed, Idx spawn, ControllerType ct);
	~Ghost();

	bool isScared();
	void setScared(bool newstate);
	void toSpawn(Idx spawn);
	void move(Level *level, Pacman *pacman);

private:
	bool scared = false;

	QString appearance, baseAppearance;
	static const QString baseScaredAppearance;
	static QString appendAppearance(QString app, Direction dir);

	GhostController *controller;

	void rotateSprite();

};

#endif // GHOST_H
