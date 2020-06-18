#ifndef CONTROLLERPREDICTIVE_H
#define CONTROLLERPREDICTIVE_H

#include "ghostcontroller.h"

class ControllerPredictive: public GhostController{
public:
	ControllerPredictive();
	~ControllerPredictive();
private:
	void findTarget(Level *level, Pacman *pacman) override;
};

#endif // CONTROLLERPREDICTIVE_H
