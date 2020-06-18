#ifndef GHOSTCONTROLLER_H
#define GHOSTCONTROLLER_H

#include "level.h"
#include "gameItems/ghost.h"
#include "gameItems/pacman.h"

#include <QRandomGenerator>


class GhostController{
public:
	GhostController(Ghost *g);
	virtual ~GhostController();

	void plan(Level* level, Pacman* pacman); //findTarget, and then navigate

	static QRandomGenerator rng; //only need 1 rng

protected:
	Ghost *ghost;

	Vec target;
	Idx lastturn;

	virtual void findTarget(Level *level, Pacman *pacman) = 0;

private:
	void navigate(Level *level); //set ghost.nextTurn depending on the ghost's target and current pos

};

#endif // GHOSTCONTROLLER_H
