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
	loadLevel("Level1");

	//init sprites
	spawnSprites();


	//init rendertimer
	QObject::connect(&rendertimer, SIGNAL(timeout()), this, SLOT(render()));

	//init fruittimer
	QObject::connect(&fruittimer, SIGNAL(timeout()), this, SLOT(spawnFruit()));
	fruittimer.setSingleShot(true);

	startTimers();

	//init message system

	msgRect.setRect(200, 200, 500, 100);
	msgRect.setBrush(QBrush(Qt::yellow));
	msgRect.setZValue(1000);
	scene->addItem(&msgRect);
	msgRect.setVisible(false);

	msgText.setBrush(QBrush(Qt::black));
	msgText.setFont(QFont("Times", 20, QFont::Bold));
	msgText.setPos(220, 230);
	msgText.setZValue(msgRect.zValue() + 1);
	scene->addItem(&msgText);
	msgText.setVisible(false);

	setFocus();

}

Game::~Game(){
	stopTimers();
	clearLevel();
	clearSprites();
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
		stopTimers();
		showMessage("Level complete! Press (N) to continue.");
	}

	//check for gameover (colligsion, loss)
	bool collision = false;
	if(collision){
		pacman->setAlive(false);
		stopTimers();
		if(lives > 1){
			lives = lives - 1;
			showMessage("Press (N) to respawn.");
		}else{
			showMessage("You died! Press (K) to quit.");
		}
	}
}

void Game::showMessage(QString msg){
	msgRect.setVisible(true);

	msgText.setText(msg);
	msgText.setVisible(true);
}

void Game::clearMessage(){
	msgRect.setVisible(false);
	msgText.setVisible(false);
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
		QRandomGenerator rng = QRandomGenerator::securelySeeded();

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
	case Qt::Key_N:
		clearMessage();
		if(level->getRemainingCoins() == 0){
			//next level
			qDebug() << "Next level baby";
			clearLevel();
			clearSprites();

			//todo: load next level here

		}else if(!pacman->isAlive()){
			//respawn

			clearSprites();
			spawnSprites();

		}
	}

}

void Game::loadLevel(QString name){
	level = new Level(name, DRAWMODE_GAME, scene);
	if(!level->isCorrectlyLoaded()){
		QMessageBox::warning(this, "LEVEL LOADING ERROR",
	"Something went wrong while loading this level. The level file is possibly corrupted. Close this message and press \"K\" to quit.");
		return;
	}
}

void Game::clearLevel(){
	delete level;
}

void Game::clearSprites(){
	//clear the ghosts
	for(int i=0; i<4; ++i)
		delete ghosts[i];

	//clear the controllers

	//clear the player
	delete pacman;
}

void Game::spawnSprites(){
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
}

void Game::startTimers(){
	rendertimer.start(FRAMETIME);
	fruittimer.start(FRUITTIME);
}

void Game::stopTimers(){
	rendertimer.stop();
	fruittimer.stop();
}

void Game::on_MainMenuButton_clicked(){
	emit MainMenuButton_clicked();
}
