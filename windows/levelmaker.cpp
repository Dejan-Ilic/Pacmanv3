#include "leveleditor.h"
#include "levelmaker.h"
#include "ui_levelmaker.h"
#include "util/constants.h"

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
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text) && levelfiles.length() > 0){
		//no pre-existing order file, so make a new one
		QString levelname = levelfiles[0];
		levelname = levelname.left(levelname.length() - 4);

		ofstream myfile;
		myfile.open ( string(LEVEL_ORDER) );
		myfile << levelname.toStdString() << endl;

		myfile.close();

		ui->selectedLevels->addItem(levelname);

	}else{
		//read order file and display it
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

void LevelMaker::saveLevelOrder(){
	QFile file(LEVEL_ORDER);

	ofstream myfile;
	myfile.open ( string(LEVEL_ORDER) );

	for(int i = 0; i < ui->selectedLevels->count(); ++i){
		QListWidgetItem* item = ui->selectedLevels->item(i);

		QString levelname = item->text();
		//levelname = levelname.left(levelname.length() - 4);


		myfile << levelname.toStdString() << endl;
	}

	myfile.close();

}

void LevelMaker::on_MainMenuButton_clicked(){
	//save levelorder
	saveLevelOrder();

	//return to menu
	emit MainMenuButton_clicked();
}


void LevelMaker::on_EditButton_clicked(){
	QString defaulttext = "";
	QList<QListWidgetItem *> selecteditems = ui->availableLevels->selectedItems();
	if(selecteditems.length() > 0){
		defaulttext = selecteditems[0]->text();
	}

	QString s = QInputDialog::getText(this, "New level name", "Name:", QLineEdit::Normal, defaulttext);
	if(s.length() == 0){
		return;
	}

	openEditor(s);

}

void LevelMaker::on_SelectButton_clicked(){
	QList<QListWidgetItem *> selecteditems = ui->availableLevels->selectedItems();
	if(selecteditems.length() == 0){
		return;
	}

	QString text = selecteditems[0]->text();

	ui->selectedLevels->addItem(text);

	saveLevelOrder();

}

void LevelMaker::on_DeselectButton_clicked(){
	QList<QListWidgetItem *> selecteditems = ui->selectedLevels->selectedItems();
	if(selecteditems.length() == 0){
		return;
	}

	ui->selectedLevels->removeItemWidget(selecteditems[0]);
	delete selecteditems[0];

	saveLevelOrder();
}

void LevelMaker::on_RenameButton_clicked(){
	QString defaulttext = "";
	QList<QListWidgetItem *> selecteditems = ui->availableLevels->selectedItems();
	if(selecteditems.length() > 0){
		defaulttext = selecteditems[0]->text();
	}else{
		return;
	}

	QString newname = QInputDialog::getText(this, "Rename level file", "New name:", QLineEdit::Normal, defaulttext);
	if(newname.length() == 0){
		return;
	}

	for(int i = 0; i < ui->selectedLevels->count(); ++i){
		QListWidgetItem* item = ui->selectedLevels->item(i);
		if(item->text() == defaulttext){
			item->setText(newname);
		}
	}
	for(int i = 0; i < ui->availableLevels->count(); ++i){
		QListWidgetItem* item = ui->availableLevels->item(i);
		if(item->text() == defaulttext){
			item->setText(newname);
		}
	}

	//rename file
	QFile file(defaulttext + LEVEL_SUFFIX);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.rename(newname + LEVEL_SUFFIX);
	file.close();

	saveLevelOrder();
}

void LevelMaker::on_UpButton_clicked(){
	QListWidgetItem *move;
	QList<QListWidgetItem *> selecteditems = ui->selectedLevels->selectedItems();
	if(selecteditems.length() > 0){
		move = selecteditems[0];
	}else{
		return;
	}

	const int C = ui->selectedLevels->count();
	int moveidx = 0;

	for(int i = 0; i < C; ++i){
		if(move == ui->selectedLevels->item(i)){
			moveidx = i;
			break;
		}
	}

	if(moveidx > 0){
		QListWidgetItem *itemA = ui->selectedLevels->item(moveidx);
		QListWidgetItem *itemB = ui->selectedLevels->item(moveidx-1);

		QString textA = itemA->text();
		QString textB = itemB->text();

		itemA->setSelected(false);
		itemB->setSelected(true);

		itemA->setText(textB);
		itemB->setText(textA);

		ui->selectedLevels->updateGeometry();

		saveLevelOrder();
	}
}

void LevelMaker::on_DownButton_clicked(){
	QListWidgetItem *move;
	QList<QListWidgetItem *> selecteditems = ui->selectedLevels->selectedItems();
	if(selecteditems.length() > 0){
		move = selecteditems[0];
	}else{
		return;
	}

	const int C = ui->selectedLevels->count();
	int moveidx = 0;

	for(int i = 0; i < C; ++i){
		if(move == ui->selectedLevels->item(i)){
			moveidx = i;
			break;
		}
	}

	if(moveidx < C-1){
		QListWidgetItem *itemA = ui->selectedLevels->item(moveidx);
		QListWidgetItem *itemB = ui->selectedLevels->item(moveidx+1);

		QString textA = itemA->text();
		QString textB = itemB->text();

		itemA->setSelected(false);
		itemB->setSelected(true);

		itemA->setText(textB);
		itemB->setText(textA);

		ui->selectedLevels->updateGeometry();

		saveLevelOrder();
	}
}

void LevelMaker::on_DeleteButton_clicked(){
	QList<QListWidgetItem *> selecteditems = ui->availableLevels->selectedItems();
	if(selecteditems.length() == 0){
		return;
	}
	QString text = selecteditems[0]->text();

	//remove from the selected levels
	const int C = ui->selectedLevels->count();

	for(int i = C - 1; i >= 0; --i){
		QListWidgetItem *item = ui->selectedLevels->item(i);

		if(text == item->text()){
			ui->selectedLevels->removeItemWidget(item);
			delete item;
		}
	}

	//remove from the available levels
	ui->availableLevels->removeItemWidget(selecteditems[0]);
	delete selecteditems[0];

	//delete file
	QFile file(text + LEVEL_SUFFIX);
	file.remove();
	file.close();

	saveLevelOrder();
}

void LevelMaker::on_CopyButton_clicked(){
	QString defaulttext = "";
	QList<QListWidgetItem *> selecteditems = ui->availableLevels->selectedItems();
	if(selecteditems.length() > 0){
		defaulttext = selecteditems[0]->text();
	}else{
		return;
	}

	QString newname = QInputDialog::getText(this, "Copy of " + defaulttext + "\'s name", "Name:", QLineEdit::Normal, defaulttext);
	if(newname.length() == 0){
		return;
	}

	ui->availableLevels->addItem(newname);

	//copy file
	QFile file(defaulttext + LEVEL_SUFFIX);
	file.copy(newname + LEVEL_SUFFIX);
	file.close();

	saveLevelOrder();
}
