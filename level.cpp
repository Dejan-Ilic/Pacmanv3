#include "level.h"
#include "constants.h"

#include <QFile>
#include <QByteArray>
#include <QDebug>

Level::Level(QString levelname, DrawMode dm, QGraphicsScene *scene): drawmode(dm), width(0), height(0){
	//read the level file

	//check if it exists
	QFile file(levelname + ".lvl");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		correctly_loaded = false;
		return;
	}
	qDebug() << "file exists";

	//check if it has consistent dimensions
	QTextStream in(&file);

	while(!in.atEnd()){
		QString line = in.readLine();
		if(width == 0){
			width = line.length();
		}else if(width != line.length()){
			correctly_loaded = false;
			return;
		}
		++height;
	}
	qDebug() << "file has consistent dimensions: H=" << height << ", W=" << width;

	//now load into tiles array
	tiles = new Tile[width * height];

	in.seek(0);
	for(int i=0; i<height; ++i){
		QString line = file.readLine();
		for(int j=0; j<width; ++j){
			char c = line.at(j).toLatin1();
			Type type = Tile::decode(c);
			if(type == spawn){
				spawnlocation = Idx(i,j);
			}

			getTile(i,j).setType(type);
			getTile(i,j).setPos_ij(i,j);
			scene->addItem(&getTile(i,j));
		}

	}

	correctly_loaded = true;

}

Level::~Level(){
	delete[] tiles;
}

Tile& Level::getTile(int i, int j){
	if(i < 0 || j < 0 || i >= height || j >= width){
		return emptytile;
	}
	return tiles[i*width + j];
}


enum Type Level::getType(int i, int j){
	Tile t = getTile(i,j);
	return t.getType();
}

void Level::setType(int i, int j, enum Type t){
	getTile(i,j).setType(t);
}

Idx Level::getSpawn(){
	return spawnlocation;
}

int Level::getWidth(){
	return width;
}

int Level::getHeight(){
	return height;
}

