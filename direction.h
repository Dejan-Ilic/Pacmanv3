#ifndef DIRECTIONS_H
#define DIRECTIONS_H

enum Direction{
	RIGHT, UP, LEFT, DOWN
};

void setDirection(int &a, int &b, Direction d);
int getPacmanRotation(Direction d);


#endif // DIRECTIONS_H
