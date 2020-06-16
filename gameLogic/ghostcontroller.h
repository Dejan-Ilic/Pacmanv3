#ifndef GHOSTCONTROLLER_H
#define GHOSTCONTROLLER_H

#include "level.h"
#include "gameItems/ghost.h"
#include "gameItems/pacman.h"

class GhostController{
public:
	GhostController(Level *level, Ghost *ghost, Pacman *pacman);
	virtual void findTarget();
	void findScaredTarget(); //the direction for when the ghost is scared

protected:
	Level *level;
	Ghost *ghost;
	Pacman *pacman;

	Idx target;
};

#endif // GHOSTCONTROLLER_H
