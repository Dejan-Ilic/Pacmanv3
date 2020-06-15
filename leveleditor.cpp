#include "leveleditor.h"

#include <QGraphicsRectItem>
#include <QBrush>
#include <Qt>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>

LevelEditor::LevelEditor(QString levelname, QWidget *parent){
	//init screen
	scene = new QGraphicsScene();
	scene->setSceneRect(0,0,800,600);

	setScene(scene);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setFixedSize(800, 600);

	setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

	//init level
	level = new Level(levelname, DRAWMODE_EDITOR, scene);

	//show modes
	const int Nlabels = 10;
	QString labels[Nlabels] = {"(E)empty", "(W)all", "ghost_(G)ate", "ghost_(F)loor", "(S)pawn",
							   "teleport(A)", "teleport(B)", "(F)ruit", "(C)oin", "(P)ill"};





}

int LevelEditor::getSelectorPos(){
	switch(this->drawmode){

	}
}

void LevelEditor::saveLevel(){
	bool leveliscorrect = true;
	QString reason = "something went wrong, you should not see this text";

	//check the level for correctness, if errors are found then report with dialogbox


	if(leveliscorrect){
		on_MainMenuButton_clicked();
	}else{
		QMessageBox::warning(this, tr("MAP EDITOR ERROR"), reason);
	}
}

void LevelEditor::keyPressEvent(QKeyEvent *event){
	const int key = event->key();

	switch(key){
	case Qt::Key_K:
		saveLevel();
		break;
	}

}

void LevelEditor::mousePressEvent(QMouseEvent *event){
	qDebug() << "le clique";
}

void LevelEditor::on_MainMenuButton_clicked(){
	emit MainMenuButton_clicked();
}
