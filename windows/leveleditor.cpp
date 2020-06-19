#include "leveleditor.h"
#include "util/constants.h"
#include "gameItems/tile.h"

#include <math.h>

#include <QGraphicsRectItem>
#include <QBrush>
#include <QKeyEvent>
#include <QMessageBox>

const Vec LevelEditor::labelpos[] = {Vec(0, 550), Vec(100, 550), Vec(200, 550), Vec(300, 550), Vec(400, 550),
									 Vec(0, 580), Vec(100, 580), Vec(200, 580), Vec(300, 580), Vec(400, 580)};
const QString LevelEditor::caption[] = {"(E)empty", "(W)all", "ghost_(G)ate", "ghost_(F)loor", "(S)pawn",
										"teleport(A)", "teleport(B)", "Frui(T)", "(C)oin", "(P)ill"};
const Type LevelEditor::drawtype[] = {empty, wall, ghost_gate, ghost_floor, spawn,
									  teleportA, teleportB, fruit, coin, pill};

LevelEditor::LevelEditor(QString levelname, QWidget *parent):
	unselected(QBrush(Qt::white)),
	selected(QBrush(Qt::red))
{
	//init screen
	scene = new QGraphicsScene();
	scene->setSceneRect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);

	setScene(scene);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

	//init level
	level = new Level(levelname, DRAWMODE_EDITOR, scene);
	if(!level->isCorrectlyLoaded()){
		QMessageBox::warning(this, "LEVEL LOADING ERROR",
	"Something went wrong while loading this level. The level file is possibly corrupted. Close this message and press \"K\" to quit.");
		return;
	}


	//init editor gui
	for(int i=0; i<Nlabels; ++i){
		typebrush = drawtype[i];
		Vec pos = labelpos[i];

		label[i] = scene->addSimpleText(caption[i]);
		label[i]->setPos(pos.x, pos.y);
		label[i]->setBrush(unselected);
	}

	//typebrush back to empty
	typebrush = empty;
	label[0]->setBrush(selected);

	//quit label
	quit = scene->addSimpleText("quit (K)");
	quit->setPos(700, 500);
	quit->setBrush(unselected);
}

LevelEditor::~LevelEditor(){
	delete quit;
	for(int i=0; i<Nlabels; ++i){
		delete label[i];
	}
}

void LevelEditor::switchBrush(Type t){
	int prev_but = getButtonIdx(typebrush);
	int next_but = getButtonIdx(t);

	typebrush = t;

	label[prev_but]->setBrush(unselected);
	label[next_but]->setBrush(selected);

}

int LevelEditor::getButtonIdx(Type t){
	switch(t){
	case empty: return 0;
	case wall: return 1;
	case ghost_gate: return 2;
	case ghost_floor: return 3;
	case spawn: return 4;

	case teleportA: return 5;
	case teleportB: return 6;
	case fruit: return 7;
	case coin: return 8;
	case pill: return 9;

	default: return 0;
	}

}

void LevelEditor::saveLevel(){
	QString reason = level->saveLevel();

	if(level->isCorrectlySaved()){
		on_MainMenuButton_clicked();
	}else{
		QMessageBox::warning(this, "LEVEL EDITOR ERROR", reason);
	}
}


void LevelEditor::keyPressEvent(QKeyEvent *event){
	const int key = event->key();

	switch(key){
	case Qt::Key_K:
		saveLevel();
		break;

	case Qt::Key_E:
		switchBrush(empty);
		break;
	case Qt::Key_W:
		switchBrush(wall);
		break;
	case Qt::Key_G:
		switchBrush(ghost_gate);
		break;
	case Qt::Key_F:
		switchBrush(ghost_floor);
		break;
	case Qt::Key_S:
		switchBrush(spawn);
		break;

	case Qt::Key_A:
		switchBrush(teleportA);
		break;
	case Qt::Key_B:
		switchBrush(teleportB);
		break;
	case Qt::Key_T:
		switchBrush(fruit);
		break;
	case Qt::Key_C:
		switchBrush(coin);
		break;
	case Qt::Key_P:
		switchBrush(pill);
		break;

	}

}

void LevelEditor::mousePressEvent(QMouseEvent *event){
	int i = floor(0.5 + (event->y() - TILE_HEIGHT/2)/static_cast<double>(TILE_HEIGHT));
	int j = floor(0.5 + (event->x() - TILE_WIDTH/2)/static_cast<double>(TILE_WIDTH));

	level->setTileType(i,j,typebrush);
}

void LevelEditor::mouseMoveEvent(QMouseEvent *event){
	mousePressEvent(event);
}

void LevelEditor::on_MainMenuButton_clicked(){
	emit MainMenuButton_clicked();
}
