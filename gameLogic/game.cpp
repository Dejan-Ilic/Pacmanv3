#include "game.h"
#include "util/constants.h"

#include <QBrush>
#include <Qt>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <QRandomGenerator>

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

	//init the controllers, which have their own timers



	//init player
	pacman = new Pacman(":/images/pacman1", NORMAL_SPEED);
	pacman->setPos_ij(level->getSpawn());
	scene->addItem(pacman);


	//init rendertimer
	QObject::connect(&rendertimer, SIGNAL(timeout()), this, SLOT(render()));
	rendertimer.start(FRAMETIME);

	//init fruittimer
	QObject::connect(&fruittimer, SIGNAL(timeout()), this, SLOT(spawnFruit()));
	fruittimer.setSingleShot(true);
	fruittimer.start(FRUITTIME);

}

Game::~Game(){
	delete level;
	delete pacman;
	for(int i=0; i<4; ++i){
		delete ghosts[i];
		//delete controller[i];
	}
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
	Type item = level->eat(pacman->getCenterPos());
	switch(item){
	case coin:
		score = score + 1;
		break;
	case pill:
		//todo: set all ghosts in pill mode
		break;
	case fruit:
		score = score + FRUIT_SCORE;
		fruittimer.start(FRUITTIME);
		break;
	}

	//check for gameover (win)
	if(level->getRemainingCoins() == 0){
		qDebug() << "You win!";
	}

	//check for gameover (colligsion, loss)
	bool collision = false;
	if(collision){
		qDebug() << "You died!";
	}




}

void Game::spawnFruit(){
	int H = level->getHeight();
	int W = level->getWidth();

	QList<Idx> list;

	for(int i=0; i<H; ++i){
		for(int j=0; j<W; ++j){
			if(level->getType(i,j) == empty){
				list.append(Idx(i,j));
			}
		}
	}

	if(list.length() > 0){
		QRandomGenerator rng;
		int i = rng.bounded(0, list.length() - 1);
		Idx v = list.at(i);

		level->setType(v.i, v.j, fruit);
	}
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

void Game::stopTimers(){
	rendertimer.stop();
	fruittimer.stop();
}

void Game::on_MainMenuButton_clicked(){
	emit MainMenuButton_clicked();
}
