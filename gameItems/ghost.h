#ifndef GHOST_H
#define GHOST_H
#include "sprite.h"

class Ghost: public Sprite{
public:
	Ghost(QString appearance, int speed, Idx spawn);
	bool isScared();
	void setScared(int time);

protected:
	bool scared = false;

	Idx spawn;

};

#endif // GHOST_H
