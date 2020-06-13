#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include "vec.h"

class Game: public QGraphicsView{
	Q_OBJECT
public:
	Game(QWidget *parent=0);

private:
	QGraphicsScene *scene;


	Vec direction = Vec();
	QGraphicsRectItem *rect;


	void keyPressEvent(QKeyEvent *event) override;

signals:
	void MainMenuButton_clicked();


private slots:
	void on_MainMenuButton_clicked();
	void moveRect();


};

#endif // GAME_H
