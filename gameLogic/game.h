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
	//technical
	bool loadingerror = false;

	//entities
	QGraphicsScene *scene;
	QTimer rendertimer;
	QTimer fruittimer;

	Pacman *pacman;
	Ghost *ghosts[4];
	GhostController *controller[4];
	Level *level;

	//leveldata
	int score = 0;
	int lives = 3;

	int levelsplayed = 0;
	int curlevel = 0;
	QStringList levellist;

	QGraphicsSimpleTextItem scoreText;
	QGraphicsSimpleTextItem livesText;
	QGraphicsSimpleTextItem levelsplayedText;

	void addScore(int amount);
	void loseLives(int amount);
	void increaseLevel(int amount);

	//event
	void keyPressEvent(QKeyEvent *event) override;

	//messages
	void showMessage(QString msg);
	void clearMessage();
	QGraphicsRectItem msgRect;
	QGraphicsSimpleTextItem msgText;

	//cleanup and startup
	void startTimers();
	void stopTimers();
	void clearSprites();
	void spawnSprites();
	void loadLevel();
	void clearLevel();
signals:
	void MainMenuButton_clicked();


private slots:
	void on_MainMenuButton_clicked();
	void render();
	void spawnFruit();


};

#endif // GAME_H
