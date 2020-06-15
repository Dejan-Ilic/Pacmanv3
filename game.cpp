#include "game.h"
#include "constants.h"

#include <QBrush>
#include <Qt>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>

#include <QTimer>

Game::Game(QWidget *parent){
	//init screen
	scene = new QGraphicsScene();
	scene->setSceneRect(0,0,800,600);

	setScene(scene);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(800, 600);

	setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

	//init level
	level = new Level("Level1", DRAWMODE_GAME, scene);
	if(!level->isCorrectlyLoaded()){
		QMessageBox::warning(this, "LEVEL LOADING ERROR",
	"Something went wrong while loading this level. The level file is possibly corrupted. Close this message and press \"K\" to quit.");
		return;
	}

	//init ghosts


	//init player
	pacman = new Sprite(":/images/pacman1", 2);
	pacman->setPos_ij(level->getSpawn());
	scene->addItem(pacman);


	//init timer
	QTimer *timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(render()));
	timer->start(FRAMETIME);

}

void Game::render(){
	pacman->move(level);
}

void Game::keyPressEvent(QKeyEvent *event){
	const int key = event->key();

	switch(key){
	case Qt::Key_Left:
		pacman->setNextDir(LEFT);
		break;
	case Qt::Key_Right:
		pacman->setNextDir(RIGHT);
		break;
	case Qt::Key_Up:
		pacman->setNextDir(UP);
		break;
	case Qt::Key_Down:
		pacman->setNextDir(DOWN);
		break;
	case Qt::Key_K:
		on_MainMenuButton_clicked();
		break;
	}

}

void Game::on_MainMenuButton_clicked(){
	emit MainMenuButton_clicked();
}
