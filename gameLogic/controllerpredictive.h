#ifndef CONTROLLERPREDICTIVE_H
#define CONTROLLERPREDICTIVE_H

#include "ghostcontroller.h"

class ControllerPredictive: public GhostController{
public:
	ControllerPredictive(Level *level, Ghost *ghost, Pacman *pacman);
private:
	void findTarget() override;
};

#endif // CONTROLLERPREDICTIVE_H
