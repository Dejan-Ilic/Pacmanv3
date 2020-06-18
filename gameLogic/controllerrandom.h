#ifndef CONTROLLERRANDOM_H
#define CONTROLLERRANDOM_H

#include "ghostcontroller.h"

class ControllerRandom: public GhostController{
public:
	ControllerRandom(Ghost *g);
	~ControllerRandom();
private:
	void findTarget(Level *level, Pacman *pacman) override;
};

#endif // CONTROLLERRANDOM_H
