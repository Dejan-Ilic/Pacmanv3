#include "leveleditor.h"
#include "levelmaker.h"
#include "ui_levelmaker.h"

#include <QDebug>
#include <QInputDialog>
#include <fstream>
using namespace std;

LevelMaker::LevelMaker(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LevelMaker)
{
	ui->setupUi(this);
	subscreen = nullptr;
}

LevelMaker::~LevelMaker(){
	delete ui;
	if(subscreen != nullptr)
		delete subscreen;
}

void LevelMaker::newSubScreen(QWidget *ss){
	subscreen = ss;
	ui->stackedWidget->addWidget(subscreen);
	connect(subscreen, SIGNAL(MainMenuButton_clicked()), this, SLOT(toFirstPage()));

	ui->stackedWidget->setCurrentIndex(1);
}

void LevelMaker::toFirstPage(){
	ui->stackedWidget->setCurrentIndex(0);
	ui->stackedWidget->removeWidget(subscreen);
	delete subscreen;
	subscreen = nullptr;
}

void LevelMaker::openEditor(QString lvlname){
	newSubScreen(new LevelEditor());
}

void LevelMaker::makeEmptyLevel(QString lvlname){
	ofstream myfile;
	myfile.open ( (lvlname + ".lvl").toStdString() );

	for(int j=0; j<WIDTH; j++){
		myfile << 'w';
	}
	myfile << endl;

	for(int i=0+1; i<HEIGHT-1; ++i){
		myfile << 'w';
		for(int j=0+1; j<WIDTH-1; ++j){
			myfile << 'e';
		}
		myfile << 'w';
		myfile << endl;
	}

	for(int j=0; j<WIDTH; j++){
		myfile << 'w';
	}
	myfile.close();
}

void LevelMaker::on_MainMenuButton_clicked(){
	emit MainMenuButton_clicked();
}


void LevelMaker::on_NewButton_clicked(){
	QString s = QInputDialog::getText(this, "New level name", "Name:");

	makeEmptyLevel(s);

	openEditor(s);

}

