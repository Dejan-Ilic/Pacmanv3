#include "direction.h"

void setDirection(int &a, int &b, Direction d){
	switch (d) {
	case RIGHT:		a = 1;	b = 0; break;
	case UP:		a = 0;	b = -1; break;
	case LEFT:		a = -1; b = 0; break;
	case DOWN:		a = 0;	b = 1; break;
	}
}

int getPacmanRotation(Direction d){
	switch (d) {
	case RIGHT:		return 180;
	case UP:		return 90;
	case LEFT:		return 0;
	case DOWN:		return 270;
	}
}

Direction opposite(Direction d){
	switch (d) {
	case RIGHT:		return LEFT;
	case UP:		return DOWN;
	case LEFT:		return RIGHT;
	case DOWN:		return UP;
	}
}
