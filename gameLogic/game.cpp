#include "controlleraggressive.h"
#include "controllerpredictive.h"
#include "controllerpursuit.h"
#include "controllerrandom.h"
#include "game.h"
#include "util/constants.h"

#include <QBrush>
#include <Qt>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QString>

Game::Game(QWidget *parent){
	//init screen
	scene = new QGraphicsScene();
	scene->setSceneRect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);

	setScene(scene);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

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

	//read level orders
	QFile file(LEVEL_ORDER);

	if( file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ExistingOnly) ){
		QTextStream in(&file);

		while(!in.atEnd()){
			QString line = in.readLine();
			levellist.append(line);
		}
		file.close();
	}

	//no levels were found...
	if(levellist.length() == 0){
		loadingerror = true;
		showMessage("No existing levels. Press (K) to quit \nand go make some levels.");

		return;
	}

	//init level
	loadLevel();

	//init sprites
	spawnSprites();

	//init rendertimer
	QObject::connect(&rendertimer, SIGNAL(timeout()), this, SLOT(render()));

	//init fruittimer
	QObject::connect(&fruittimer, SIGNAL(timeout()), this, SLOT(spawnFruit()));
	fruittimer.setSingleShot(true);

	//init releasetimer
	QObject::connect(&releasetimer, SIGNAL(timeout()), this, SLOT(releaseGhosts()));

	startTimers();

	//init info texts
	scoreText.setBrush(QBrush(Qt::white));
	scoreText.setFont(QFont("Times", 20, QFont::Bold));
	scoreText.setPos(100, 560);
	scene->addItem(&scoreText);
	addScore(0);

	livesText.setBrush(QBrush(Qt::white));
	livesText.setFont(QFont("Times", 20, QFont::Bold));
	livesText.setPos(300, 560);
	scene->addItem(&livesText);
	loseLives(0);

	levelsplayedText.setBrush(QBrush(Qt::white));
	levelsplayedText.setFont(QFont("Times", 20, QFont::Bold));
	levelsplayedText.setPos(500, 560);
	scene->addItem(&levelsplayedText);
	increaseLevel(0);

	//the pill timer
	QObject::connect(&pilltimer, SIGNAL(timeout()), this, SLOT(pillCountDown()));

	pillText.setBrush(QBrush(Qt::white));
	pillText.setFont(QFont("Times", 20, QFont::Bold));
	pillText.setPos(300, 500);
	pillText.setVisible(false);
	scene->addItem(&pillText);

}

Game::~Game(){
	if(!loadingerror){
		stopTimers();
		clearLevel();
		clearSprites();
	}
}

void Game::render(){
	//move monsieur pacman
	pacman->move(level);

	//move les phantomes
	for(int i=0; i<4; ++i){
		ghosts[i]->move(level, pacman);
	}


	//eat the coins and other items
	Type item = level->eat(pacman->getCenterPos());
	switch(item){
	case coin:
		addScore(1);
		break;
	case pill:
		//set all active ghosts in pill mode
		for(int i=0; i<4; ++i){
			if(ghosts[i]->isAlive()){
				ghosts[i]->setScared(true);
			}
		}
		pillLevel = pillLevel + MAX_PILL_LEVEL;
		if(!pilltimer.isActive()){
			pilltimer.start(PILL_DECREASE_TIME);
		}
		showPillText();
		break;
	case fruit:
		addScore(FRUIT_SCORE);
		fruittimer.start(FRUITTIME);
		break;
	}

	//check for gameover (win)
	if(level->getRemainingCoins() == 0){
		stopTimers();
		showMessage("Level complete! Press (N) to continue.");
	}

	//check for gameover (collision, loss) and eat scared ghosts
	bool collision = false;

	Vec pacpos = pacman->getCenterPos();

	for(int i=0; i<4; ++i){
		if(pacpos.l1dist(ghosts[i]->getCenterPos()) <= EAT_DIST){
			if(ghosts[i]->isScared()){
				addScore(GHOSTEAT_SCORE);
				respawnGhost(i);
			}else{
				collision = true;
			}
		}
	}

	if(collision){
		pacman->setAlive(false);
		stopTimers();
		loseLives(1);
		if(lives > 0){
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

		int i = rng.bounded(0, list.length());
		Idx v = list.at(i);

		level->setType(v.i, v.j, fruit);
	}
}

void Game::keyPressEvent(QKeyEvent *event){
	const int key = event->key();

	if(loadingerror){
		on_MainMenuButton_clicked();
		return;
	}

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
		if(level->getRemainingCoins() == 0){
			clearMessage();
			hidePillText();

			//next level
			clearLevel();
			clearSprites();

			increaseLevel(1);

			loadLevel();
			spawnSprites();
			startTimers();

		}else if(!pacman->isAlive() && lives > 0){
			clearMessage();

			//respawn
			clearSprites();
			spawnSprites();
			startTimers();
		}
	}

}

void Game::addScore(int amount){
	score = score + amount;
	scoreText.setText(QString("Score: %1").arg(score));
}
void Game::loseLives(int amount){
	lives = lives - amount;
	livesText.setText(QString("Lives: %1").arg(lives));

}
void Game::increaseLevel(int amount){
	curlevel = (curlevel + amount)%levellist.length();
	levelsplayed = levelsplayed + amount;
	levelsplayedText.setText(QString("Levels played: %1").arg(levelsplayed));
}

void Game::loadLevel(){
	QString name = levellist.at(curlevel);

	level = new Level(name, DRAWMODE_GAME, scene);
	if(!level->isCorrectlyLoaded()){
		QMessageBox::warning(this, "LEVEL LOADING ERROR",
	"Something went wrong while loading this level. The level file is possibly corrupted. Close this message and press (K) to quit.");
		return;
	}
}

void Game::clearLevel(){
	if(level != nullptr){
		delete level;
		level = nullptr;
	}
}

void Game::respawnGhost(int i){
	ghosts[i]->toSpawn(level->getGhostSpawn(i));
	ghosts[i]->setScared(false);
	ghosts[i]->setAlive(false);
}

void Game::showPillText(){
	pillText.setVisible(true);
	updatePillText();

}

void Game::hidePillText(){
	pillText.setVisible(false);
}

void Game::updatePillText(){
	pillText.setText("<" + QString("|").repeated(pillLevel) );
}

void Game::clearSprites(){
	//clear the ghosts
	for(int i=0; i<4; ++i){
		if(ghosts[i] != nullptr){
			delete ghosts[i];
			ghosts[i] = nullptr;
		}
	}

	//clear the player
	if(pacman != nullptr){
		delete pacman;
		pacman = nullptr;
	}
}

void Game::spawnSprites(){
	//init player
	pacman = new Pacman(":/images/pacman1", NORMAL_SPEED);
	pacman->setPos_ij(level->getSpawn());
	scene->addItem(pacman);

	//init ghosts
	QString ghostcolors[4] = {"red", "green", "blue", "yellow"};


	ghosts[0] = new Ghost(":/images/ghost_"+ghostcolors[0], NORMAL_SPEED, level->getGhostSpawn(0), AGGRESSIVE);
	ghosts[1] = new Ghost(":/images/ghost_"+ghostcolors[1], NORMAL_SPEED, level->getGhostSpawn(1), PREDICTIVE);
	ghosts[2] = new Ghost(":/images/ghost_"+ghostcolors[2], NORMAL_SPEED, level->getGhostSpawn(2), PURSUIT);
	ghosts[3] = new Ghost(":/images/ghost_"+ghostcolors[3], NORMAL_SPEED, level->getGhostSpawn(3), RANDOM);

	//now add them to the scene
	for(int i=0; i<4; ++i){
		scene->addItem(ghosts[i]);
	}
}

void Game::releaseGhosts(){
	int totcoins = level->getTotalCoins();
	int remcoins = level->getRemainingCoins();
	float frac = remcoins/(static_cast<float>(totcoins) + 1); //don't divide by zero

	float thresholds[4] = RELEASE_THRESHOLDS;

	for(int i=0; i<4; ++i){
		if(!ghosts[i]->isAlive() && frac <= thresholds[i]){
			ghosts[i]->setAlive(true);
		}
	}

}

void Game::pillCountDown(){
	pillLevel = pillLevel - 1;
	if(pillLevel == 0){
		hidePillText();
		pilltimer.stop();

		for(int i=0; i<4; ++i){
			ghosts[i]->setScared(false);
		}

	}else{
		updatePillText();
	}
}

void Game::startTimers(){
	rendertimer.start(FRAMETIME);
	fruittimer.start(FRUITTIME);
	releasetimer.start(2000);
}

void Game::stopTimers(){
	rendertimer.stop();
	fruittimer.stop();
	releasetimer.stop();
	pilltimer.stop();
}

void Game::on_MainMenuButton_clicked(){
	emit MainMenuButton_clicked();
}
