#ifndef PACMAN_H
#define PACMAN_H
#include "sprite.h"

class Pacman: public Sprite{
public:
	Pacman(QString appearance, int speed);

private:
	void rotateSprite() override;
};

#endif // PACMAN_H
