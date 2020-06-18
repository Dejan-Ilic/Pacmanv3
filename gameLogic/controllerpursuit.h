#ifndef CONTROLLERPURSUIT_H
#define CONTROLLERPURSUIT_H

#include "ghostcontroller.h"

class ControllerPursuit: public GhostController{
public:
	ControllerPursuit(Ghost *g);
	~ControllerPursuit();
private:
	void findTarget(Level *level, Pacman *pacman) override;
};

#endif // CONTROLLERPURSUIT_H
