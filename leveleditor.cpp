#include "leveleditor.h"
#include "constants.h"

#include <math.h>

#include <QGraphicsRectItem>
#include <QBrush>
#include <QKeyEvent>
#include <QDebug>
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
	scene->setSceneRect(0,0,800,600);

	setScene(scene);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(800, 600);

	setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

	//init level
	level = new Level(levelname, DRAWMODE_EDITOR, scene);

	for(int i=0; i<Nlabels; ++i){
		drawmode = drawtype[i];
		Vec pos = labelpos[i];

		label[i] = scene->addSimpleText(caption[i]);
		label[i]->setPos(pos.x, pos.y);
		label[i]->setBrush(unselected);
	}

	//drawmode back to empty
	drawmode = empty;
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

void LevelEditor::switchMode(Type t){
	int prev_but = getButtonIdx(drawmode);
	int next_but = getButtonIdx(t);

	drawmode = t;

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
	bool leveliscorrect = true;
	QString reason = "something went wrong, you should not see this text";

	//check the level for correctness, if errors are found then report with dialogbox


	if(leveliscorrect){
		on_MainMenuButton_clicked();
	}else{
		QMessageBox::warning(this, tr("MAP EDITOR ERROR"), reason);
	}
}


void LevelEditor::keyPressEvent(QKeyEvent *event){
	const int key = event->key();

	switch(key){
	case Qt::Key_K:
		saveLevel();
		break;

	case Qt::Key_E:
		switchMode(empty);
		break;
	case Qt::Key_W:
		switchMode(wall);
		break;
	case Qt::Key_G:
		switchMode(ghost_gate);
		break;
	case Qt::Key_F:
		switchMode(ghost_floor);
		break;
	case Qt::Key_S:
		switchMode(spawn);
		break;

	case Qt::Key_A:
		switchMode(teleportA);
		break;
	case Qt::Key_B:
		switchMode(teleportB);
		break;
	case Qt::Key_T:
		switchMode(fruit);
		break;
	case Qt::Key_C:
		switchMode(coin);
		break;
	case Qt::Key_P:
		switchMode(pill);
		break;

	}

}

void LevelEditor::mousePressEvent(QMouseEvent *event){
	int i = floor(0.5 + (event->y() - TILE_HEIGHT/2)/static_cast<double>(TILE_HEIGHT));
	int j = floor(0.5 + (event->x() - TILE_WIDTH/2)/static_cast<double>(TILE_WIDTH));

	qDebug() << "le clique: " << i << ", " << j;

	level->setType(i,j,drawmode);
}

void LevelEditor::on_MainMenuButton_clicked(){
	emit MainMenuButton_clicked();
}
