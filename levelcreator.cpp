#include "levelcreator.h"

#include <QGraphicsRectItem>
#include <QBrush>
#include <Qt>
#include <QKeyEvent>
#include <QDebug>

LevelCreator::LevelCreator(QWidget *parent){
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

void LevelCreator::keyPressEvent(QKeyEvent *event){
	const int key = event->key();

	switch(key){
	case Qt::Key_K:
		qDebug() << "k";
		on_backToLevelMaker();
		break;
	}

}

void LevelCreator::on_backToLevelMaker(){
	emit backToLevelMaker();
}
