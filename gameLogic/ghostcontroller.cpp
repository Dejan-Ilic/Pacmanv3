#include "ghostcontroller.h"

QRandomGenerator GhostController::rng = QRandomGenerator::securelySeeded();


GhostController::GhostController(Ghost *g): ghost(g){

}

GhostController::~GhostController(){

}

void GhostController::plan(Level* level, Pacman *pacman){
	if(!ghost->isAlive()){
		ghost->setNextDir(opposite(ghost->getCurDir())); //some uneasy back and forth waiting
		return;
	}

	//first find the target square, using derived class findtarget!!!
	if(!ghost->isScared()){
		findTarget(level, pacman);
	}

	//then navigate, i.e. decide what turn to take
	navigate(level);
}

void GhostController::navigate(Level *level){
	Idx ghostidx = ghost->getIdx();
	Vec squarecenter = Visual::idxToCenteredVec(ghostidx);
	Vec ghostcenter = ghost->getCenterPos();

	if(ghostidx != lastturn && ghostcenter.l1dist(squarecenter) <= ghost->getSpeed()){
		lastturn = ghostidx;

		//let me exit the ghost waiting room!
		Type underme = level->getTileType(ghostidx);
		if(underme == ghost_floor || underme == ghost_gate){
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
			Type type = level->getTileType(candidates.at(i));
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














