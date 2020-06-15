#include "leveleditor.h"
#include "levelmaker.h"
#include "ui_levelmaker.h"
#include "constants.h"

#include <QDebug>
#include <QDir>
#include <QInputDialog>
#include <fstream>
#include <string>
using namespace std;


LevelMaker::LevelMaker(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LevelMaker)
{
	ui->setupUi(this);
	subscreen = nullptr;

	updateLists();

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

void LevelMaker::updateLists(){
	//init the available levels
	ui->availableLevels->clear();
	QDir directory(".");
	QStringList levelfiles = directory.entryList(QStringList() << "*.lvl", QDir::Files);

	foreach(QString levelname, levelfiles) {
		QString lvl = levelname.left(levelname.length()-4);
		ui->availableLevels->addItem(lvl);
	}

	//init selected levels
	ui->selectedLevels->clear();
	QFile file(LEVEL_ORDER);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text) && levelfiles.length() > 0){//nothing found, so
		QString levelname = levelfiles[0];
		levelname = levelname.left(levelname.length() - 4);

		ofstream myfile;
		myfile.open ( string(LEVEL_ORDER) );
		myfile << levelname.toStdString() << endl;

		myfile.close();

		ui->selectedLevels->addItem(levelname);

	}else{
		QTextStream in(&file);

		while(!in.atEnd()){
			QString line = in.readLine();
			ui->selectedLevels->addItem(line);
		}

	}
	file.close();
}

void LevelMaker::toFirstPage(){
	ui->stackedWidget->setCurrentIndex(0);
	ui->stackedWidget->removeWidget(subscreen);
	delete subscreen;
	subscreen = nullptr;

	updateLists();
}

void LevelMaker::openEditor(QString lvlname){
	newSubScreen(new LevelEditor(lvlname));
}

void LevelMaker::on_MainMenuButton_clicked(){
	emit MainMenuButton_clicked();
}


void LevelMaker::on_EditButton_clicked(){
	QString defaulttext = "";
	QList<QListWidgetItem *> selecteditems = ui->availableLevels->selectedItems();
	if(selecteditems.length() > 0){
		defaulttext = selecteditems[0]->text();
	}


	QString s = QInputDialog::getText(this, "New level name", "Name:", QLineEdit::Normal, defaulttext);


	openEditor(s);

}

void LevelMaker::on_SelectButton_clicked()
{

}

void LevelMaker::on_DeleteButton_clicked()
{

}

void LevelMaker::on_DeselectButton_clicked()
{

}

void LevelMaker::on_UpButton_clicked()
{

}

void LevelMaker::on_DownButton_clicked()
{

}

void LevelMaker::on_RenameButton_clicked()
{

}
