#include "level.h"
#include "util/constants.h"

#include <QFile>
#include <QString>
#include <QByteArray>
#include <QTextStream>

#include <fstream>
#include <string>

Level::Level(QString levelname, DrawMode dm, QGraphicsScene *scene):
	levelname(levelname),
	width(0), height(0),
	drawmode(dm),
	scene(scene)
{
	voidsquare.setType(error);

	//read the level file
	loadLevel();

}

Level::~Level(){
	delete[] tiles;
}

Tile& Level::getTile(int i, int j){
	if(i < 0 || j < 0 || i >= height || j >= width){
		return voidsquare;
	}
	return tiles[i*width + j];
}

bool Level::loadLevel(){
	//check if it exists
	QFile file(levelname + LEVEL_SUFFIX);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text |  QIODevice::ExistingOnly)){//nothing found, so make standard level
		width = LEVEL_WIDTH;
		height = LEVEL_HEIGHT;

		tiles = new Tile[width * height];

		for(int j=0; j<width; j++){
			initTile(0,j,wall);
		}

		for(int i=0+1; i<height-1; ++i){
			initTile(i,0,wall);
			for(int j=0+1; j<width-1; ++j){
				initTile(i,j,empty);
			}
			initTile(i,width-1,wall);
		}

		setType(height-2, width/2, spawn);
		setType(1,1,ghost_floor);
		setType(2,1,ghost_floor);
		setType(1,2,ghost_floor);
		setType(2,2,ghost_floor);

		setType(3,1,ghost_gate);
		setType(3,2,ghost_gate);

		setType(1,3,wall);
		setType(2,3,wall);
		setType(3,3,wall);

		setType(height-2, width/2 + 1, coin);

		for(int j=0; j<width; j++){
			initTile(height-1,j,wall);
		}
	}else{
		//check if it has consistent dimensions
		QTextStream in(&file);

		while(!in.atEnd()){
			QString line = in.readLine();
			if(width == 0){
				width = line.length();
			}else if(width != line.length()){
				correctly_loaded = false;
				return false;
			}
			++height;
		}

		//now load into tiles array
		tiles = new Tile[width * height];

		in.seek(0);
		for(int i=0; i<height; ++i){
			QString line = file.readLine();
			for(int j=0; j<width; ++j){
				char c = line.at(j).toLatin1();
				Type type = Tile::decode(c);
				initTile(i,j,type);
			}

		}

		file.close();

	}

	//now find all useful squares:
	int nspawns = 0;

	for(int i=0; i<height; ++i){
		for(int j=0; j<width; ++j){
			Type type = getType(i,j);
			if(type == spawn){
				spawnlocation = Idx(i,j);
			}else if(type == ghost_floor && nspawns < 4){
				ghostspawns[nspawns] = Idx(i,j);
				++nspawns;
			}else if(type == coin){
				++numcoins;
			}
		}
	}

	totalcoins = numcoins;


	correctly_loaded = true;
	return true;
}


QString Level::saveLevel(){
	correctly_saved = false;
	if(drawmode != DRAWMODE_EDITOR){
		return "Cannot save levels in game mode!";
	}

	//check all conditions
	{
		Type tij;
		//condition 1: outer walls
		for(int i=0; i<LEVEL_HEIGHT; ++i){
			tij = getType(i,0);
			if(tij != wall && tij != teleportA && tij != teleportB){
				correctly_saved = false;
				return "Missing outer wall";
			}
		}
		for(int i=0; i<LEVEL_HEIGHT; ++i){
			tij = getType(i,LEVEL_WIDTH-1);
			if(tij != wall && tij != teleportA && tij != teleportB){
				correctly_saved = false;
				return "Missing outer wall";
			}
		}
		for(int j=0; j<LEVEL_WIDTH; ++j){
			tij = getType(0,j);
			if(tij != wall && tij != teleportA && tij != teleportB){
				correctly_saved = false;
				return "Missing outer wall";
			}
		}
		for(int j=0; j<LEVEL_WIDTH; ++j){
			tij = getType(LEVEL_HEIGHT-1,j);
			if(tij != wall && tij != teleportA && tij != teleportB){
				correctly_saved = false;
				return "Missing outer wall";
			}
		}
		//condition 2: counts
		int spawncount = 0; //should be 1
		int tpAcount = 0, tpBcount = 0; //teleports: a=b=1 or 0;
		int gfcount = 0, ggcount = 0; //4 ghost floors needed, 2 ghost gates needed

		for(int i=0; i<LEVEL_HEIGHT; ++i){
			for(int j=0; j<LEVEL_WIDTH; ++j){
				tij = getType(i,j);
				switch(tij){
				case spawn: ++spawncount; break;
				case teleportA: ++tpAcount; break;
				case teleportB: ++tpBcount; break;
				case ghost_gate: ++ggcount; break;
				case ghost_floor: ++gfcount; break;
				}
			}
		}

		if(spawncount != 1){
			correctly_saved = false;
			return QString("Exactly 1 spawn is needed, %1 were found.").arg(spawncount);
		}else if(tpAcount > 1 || tpBcount > 1 || tpAcount != tpBcount){
			correctly_saved = false;
			return "Exactly 0 of both teleportA and teleportB are needed or exactly 1 of both.";
		}else if(ggcount != 2){
			correctly_saved = false;
			return QString("Exactly 2 ghost gates are needed, %1 were found.").arg(ggcount);
		}else if(gfcount != 4){
			correctly_saved = false;
			return QString("Exactly 4 ghost floors are needed, %1 were found.").arg(gfcount);
		}

	}
	//now save the file
	std::ofstream myfile;
	myfile.open ( (levelname + LEVEL_SUFFIX).toStdString() );
	for(int i=0; i<LEVEL_HEIGHT; ++i){
		for(int j=0; j<LEVEL_WIDTH; ++j){
			myfile << Tile::encode(this->getType(i,j));
		}
		myfile << std::endl;
	}
	myfile.close();

	correctly_saved = true;
	return "Save succesful";
}

enum Type Level::getType(int i, int j) const{
	Tile t = tiles[i*width + j]; //cannot use getTile
	return t.getType();
}

enum Type Level::getType(const Idx &v) const{
	return getType(v.i, v.j);
}

void Level::setType(int i, int j, enum Type t){
	getTile(i,j).setType(t);
}

void Level::initTile(int i, int j, enum Type t){
	setType(i, j, t);
	getTile(i,j).setPos_ij(i,j);
	scene->addItem(&getTile(i,j));
}

bool Level::isCorrectlyLoaded() const{
	return correctly_loaded;
}

bool Level::isCorrectlySaved() const{
	return correctly_saved;
}

Idx Level::getSpawn() const{
	return spawnlocation;
}

int Level::getWidth() const{
	return width;
}

int Level::getHeight() const{
	return height;
}

Type Level::eat(int x, int y){
	return eat(Vec(x,y));
}


Type Level::eat(Vec v){
	Idx p = Visual::centeredVecToIdx(v);
	Vec pCenter = Visual::idxToCenteredVec(p);

	//v: pacman pos, p: square he is in, pCenter: center pos of that square

	Type type = getType(p);
	bool edible = (type == coin || type == fruit || type == pill);

	if(edible && v.l1dist(pCenter) <= EAT_DIST){
		setType(p.i, p.j, empty);

		if(type == coin){
			numcoins = numcoins - 1;
		}
	}else{
		type = empty;
	}

	return type;

}

int Level::getRemainingCoins() const{
	return numcoins;
}

int Level::getTotalCoins() const{
	return totalcoins;
}

Idx Level::getGhostSpawn(int i) const{
	if(i < 0 || i >= 4){
		i = 0;
	}
	return ghostspawns[i];
}


