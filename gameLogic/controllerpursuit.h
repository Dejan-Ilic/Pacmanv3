#ifndef CONTROLLERPURSUIT_H
#define CONTROLLERPURSUIT_H

#include "ghostcontroller.h"

class ControllerPursuit: public GhostController{
public:
	ControllerPursuit(Level *level, Ghost *ghost, Pacman *pacman);
private:
	void findTarget() override;
};

#endif // CONTROLLERPURSUIT_H
