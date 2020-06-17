#include "ghostcontroller.h"

QRandomGenerator GhostController::rng = QRandomGenerator::securelySeeded();


GhostController::GhostController(Level *level, Ghost *ghost, Pacman *pacman):
	level(level), ghost(ghost), pacman(pacman)
{

}

void GhostController::plan(){
	if(!active){
		ghost->setNextDir(opposite(ghost->getCurDir())); //some uneasy back and forth waiting
		return;
	}

	//first find the target square, using derived class findtarget!!!
	if(!ghost->isScared()){
		findTarget();
	}

	//then navigate
	navigate();
}

void GhostController::setActive(bool a){
	active = a;
}

void GhostController::navigate(){
	Idx ghostidx = ghost->getIdx();
	Vec squarecenter = Visual::idxToCenteredVec(ghostidx);
	Vec ghostcenter = ghost->getCenterPos();

	if( ghostcenter.l1dist(squarecenter) <= ghost->getSpeed()){
		//let me exit the ghost waiting room!
		if(level->getType(ghostidx) == ghost_floor){
			ghost->setCanPassGate(true);
		}else{
			ghost->setCanPassGate(false);
		}


		//what turn can I make?
		Direction lookCur = ghost->getCurDir();

		Direction lookA, lookB;

		if(lookCur == UP || lookCur == DOWN){
			lookA = LEFT;
			lookB = RIGHT;
		}else{
			lookA = UP;
			lookB = DOWN;
		}

		Idx sqCur = ghostidx + Idx(lookCur); //nxt square
		Idx sqA = ghostidx + Idx(lookA); //lookA sq
		Idx sqB = ghostidx + Idx(lookB); //lookB sq

		QList<Idx> candidates = {sqCur, sqA, sqB};
		QList<Direction> candidatedirections = {lookCur, lookA, lookB};

		for(int i=2; i>=0; --i){
			Type type = level->getType(candidates.at(i));
			if(type == wall || (type == ghost_gate && !ghost->getCanPassGate())){
				candidates.removeAt(i);
				candidatedirections.removeAt(i);
			}
		}

		//in scared mode, just do some random stuff:
		if(ghost->isScared()){
			ghost->setNextDir(candidatedirections.at(rng.bounded(0,candidatedirections.length())));

		}else{
			Direction bestdir = ghost->getCurDir();

			if(candidates.length() == 0){
				//go in the opposite direction
				bestdir = opposite(ghost->getCurDir());

			}else{
				//look for direction that minimizes l2 (squared) distance to target
				int mindist = INT_MAX;

				for(int i=0; i<candidates.length(); ++i){
					Vec nextsquare = Visual::idxToCenteredVec(candidates.at(i));
					int dist = nextsquare.l2distSquared(target);
					if(dist < mindist){
						mindist = dist;
						bestdir = candidatedirections.at(i);
					}
				}
			}

			ghost->setNextDir(bestdir);
		}
	}
}














