#ifndef GHOSTCONTROLLER_H
#define GHOSTCONTROLLER_H

#include "level.h"
#include "gameItems/ghost.h"
#include "gameItems/pacman.h"

#include <QRandomGenerator>

class GhostController{
public:
	GhostController(Level *level, Ghost *ghost, Pacman *pacman);
	virtual ~GhostController();


	void plan(); //findTarget, and then navigate
	void setActive(bool a);
	bool isActive();

	static QRandomGenerator rng; //only need 1 rng

protected:
	Level *level;
	Ghost *ghost;
	Pacman *pacman;

	Vec target;
	Idx lastturn;

	virtual void findTarget() = 0;

private:
	void navigate(); //set ghost.nextTurn depending on the ghost's target and current pos
	bool active = false;
};

#endif // GHOSTCONTROLLER_H
