#ifndef CONTROLLERRANDOM_H
#define CONTROLLERRANDOM_H

#include "ghostcontroller.h"

class ControllerRandom: public GhostController{
public:
	ControllerRandom(Level *level, Ghost *ghost, Pacman *pacman);
private:
	void findTarget() override;
};

#endif // CONTROLLERRANDOM_H
