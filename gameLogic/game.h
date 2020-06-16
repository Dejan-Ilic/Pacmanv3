#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>

#include "util/vec.h"
#include "gameItems/pacman.h"
#include "level.h"
#include "gameItems/ghost.h"
#include "ghostcontroller.h"


class Game: public QGraphicsView{
	Q_OBJECT
public:
	Game(QWidget *parent=0);
	~Game();

private:
	QGraphicsScene *scene;
	QTimer rendertimer;
	QTimer fruittimer;

	Pacman *pacman;
	Ghost *ghosts[4];
	GhostController *controller[4];
	Level *level;

	int score = 0;
	int lives = 3;

	void keyPressEvent(QKeyEvent *event) override;
	void stopTimers();

signals:
	void MainMenuButton_clicked();


private slots:
	void on_MainMenuButton_clicked();
	void render();
	void spawnFruit();


};

#endif // GAME_H
