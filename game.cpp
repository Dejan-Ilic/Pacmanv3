#include "game.h"

#include <QGraphicsRectItem>
#include <QBrush>
#include <Qt>
#include <QKeyEvent>
#include <QDebug>

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
	QGraphicsRectItem *rect = new QGraphicsRectItem();
	rect->setRect(300,400,100,100);
	scene->addItem(rect);

}

void Game::keyPressEvent(QKeyEvent *event){
	const int key = event->key();

	switch(key){
	case Qt::Key_Left:
		qDebug() << "left";
		break;
	case Qt::Key_Right:
		qDebug() << "right";
		break;
	case Qt::Key_Up:
		qDebug() << "up";
		break;
	case Qt::Key_Down:
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
