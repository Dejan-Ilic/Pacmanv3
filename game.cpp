#include "game.h"
#include "constants.h"

#include <QBrush>
#include <Qt>
#include <QKeyEvent>
#include <QDebug>

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

	//init ghosts


	//init player
	pacman = new Sprite(":/images/pacman1", 4);
	pacman->setPos(100,100);
	scene->addItem(pacman);


	//init timer
	QTimer *timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(render()));
	timer->start(FRAMETIME);

}

void Game::render(){
	pacman->move(nullptr);
}

void Game::keyPressEvent(QKeyEvent *event){
	const int key = event->key();

	switch(key){
	case Qt::Key_Left:
		pacman->setNextDir(-1,0);
		qDebug() << "left";
		break;
	case Qt::Key_Right:
		pacman->setNextDir(1,0);
		qDebug() << "right";
		break;
	case Qt::Key_Up:
		pacman->setNextDir(0, -1);
		qDebug() << "up";
		break;
	case Qt::Key_Down:
		pacman->setNextDir(0,1);
		qDebug() << "down";
		break;
	case Qt::Key_K:
		qDebug() << "k";
		on_MainMenuButton_clicked();
		break;
	}

}

void Game::on_MainMenuButton_clicked(){
	emit MainMenuButton_clicked();
}
