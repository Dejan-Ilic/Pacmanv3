#ifndef GHOST_H
#define GHOST_H
#include "pacman.h"
#include "sprite.h"

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
	QString appearance;
	GhostController *controller;

};

#endif // GHOST_H
