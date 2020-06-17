#ifndef GHOSTCONTROLLER_H
#define GHOSTCONTROLLER_H

#include "level.h"
#include "gameItems/ghost.h"
#include "gameItems/pacman.h"

#include <QRandomGenerator>

class GhostController{
public:
	GhostController(Level *level, Ghost *ghost, Pacman *pacman);
	virtual void findTarget();
	void findScaredTarget(); //the target for when the ghost is scared

	void navigate(); //set ghost.nextTurn depending on the ghost's target and current pos

	static QRandomGenerator rng; //only need 1 rng

protected:
	Level *level;
	Ghost *ghost;
	Pacman *pacman;

	Vec target;
};

#endif // GHOSTCONTROLLER_H
