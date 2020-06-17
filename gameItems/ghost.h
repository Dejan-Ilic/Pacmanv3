#ifndef GHOST_H
#define GHOST_H
#include "sprite.h"

class Ghost: public Sprite{
public:
	Ghost(QString appearance, int speed, Idx spawn);
	bool isScared();
	void setScared(bool newstate);
	void toSpawn();

private:
	bool scared = false;
	Idx spawn;
	QString appearance;

};

#endif // GHOST_H
