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
	QString ghostcolors[4] = {"red", "green", "blue", "yellow"};
	for(int i=0; i<4; ++i){
		ghosts[i] = new Ghost(":/images/ghost_"+ghostcolors[i], NORMAL_SPEED, level->getGhostSpawn(i));
		scene->addItem(ghosts[i]);
	}

	//init the controllers




	//init player
	pacman = new Pacman(":/images/pacman1", NORMAL_SPEED);
	pacman->setPos_ij(level->getSpawn());
	scene->addItem(pacman);


	//init timer
	QTimer *timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(render()));
	timer->start(FRAMETIME);

}

void Game::render(){
	//move monsieur pacman
	pacman->move(level);

	//move les phantomes
	/*
	for(int i=0; i<4; ++i){
		ghostcontrollers[i].calcDirections();
		ghosts[i]->move(level);
	}
	*/

	//eat the coins and other items



	//check for gameover



	//check for collisions


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
