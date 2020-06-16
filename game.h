#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include "vec.h"
#include "pacman.h"
#include "level.h"
#include "ghost.h"


class Game: public QGraphicsView{
	Q_OBJECT
public:
	Game(QWidget *parent=0);

private:
	QGraphicsScene *scene;
	Pacman *pacman;
	Ghost *ghosts[4];
	Level *level;

	void keyPressEvent(QKeyEvent *event) override;

signals:
	void MainMenuButton_clicked();


private slots:
	void on_MainMenuButton_clicked();
	void render();


};

#endif // GAME_H
