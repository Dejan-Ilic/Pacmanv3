#ifndef GHOSTCONTROLLER_H
#define GHOSTCONTROLLER_H

#include "level.h"
#include "gameItems/ghost.h"
#include "gameItems/pacman.h"

class GhostController{
public:
	GhostController(Level *level, Ghost *ghost, Pacman *pacman);
	virtual void findGhostDirection() = 0;
	void findScaredDirection(); //the direction for when the ghost is scared

protected:
	Level *level;
	Ghost *ghost;
	Pacman *pacman;
};

#endif // GHOSTCONTROLLER_H
