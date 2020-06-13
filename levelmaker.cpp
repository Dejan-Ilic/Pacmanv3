#include "leveleditor.h"
#include "levelmaker.h"
#include "ui_levelmaker.h"

#include <QInputDialog>

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

}

void LevelMaker::on_MainMenuButton_clicked(){
	emit MainMenuButton_clicked();
}


void LevelMaker::on_NewButton_clicked(){
	QString s = QInputDialog::getText(this, "New level name", "Name:");

	makeEmptyLevel(s);

	openEditor(s);

}

