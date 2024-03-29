#ifndef CONTROLLERAGGRESSIVE_H
#define CONTROLLERAGGRESSIVE_H

#include "ghostcontroller.h"

class ControllerAggressive : public GhostController{
public:
	ControllerAggressive(Ghost *g);
	~ControllerAggressive();
private:
	void findTarget(Level *level, Pacman *pacman) override;
};

#endif // CONTROLLERAGGRESSIVE_H
