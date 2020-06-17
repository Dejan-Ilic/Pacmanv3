#ifndef CONTROLLERAGGRESSIVE_H
#define CONTROLLERAGGRESSIVE_H

#include "ghostcontroller.h"

class ControllerAggressive : public GhostController{
public:
	ControllerAggressive(Level *level, Ghost *ghost, Pacman *pacman);
private:
	void findTarget() override;
};

#endif // CONTROLLERAGGRESSIVE_H
