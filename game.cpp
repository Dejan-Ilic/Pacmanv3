#include "game.h"

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

	//setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

	//init player
	rect = new QGraphicsRectItem();
	rect->setRect(300,400,100,100);
	scene->addItem(rect);

	QTimer *timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(moveRect()));
	timer->start(1000/60.0);

}

void Game::moveRect(){
	rect->setPos(rect->x() + direction.x, rect->y() + direction.y);
}

void Game::keyPressEvent(QKeyEvent *event){
	const int key = event->key();

	switch(key){
	case Qt::Key_Left:
		direction = Vec(-1,0);
		qDebug() << "left";
		break;
	case Qt::Key_Right:
		direction = Vec(1,0);
		qDebug() << "right";
		break;
	case Qt::Key_Up:
		direction = Vec(0, -1);
		qDebug() << "up";
		break;
	case Qt::Key_Down:
		direction = Vec(0,1);
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
