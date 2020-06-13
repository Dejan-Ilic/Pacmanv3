#include "levelmaker.h"
#include "ui_levelmaker.h"

LevelMaker::LevelMaker(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LevelMaker)
{
	ui->setupUi(this);
}

LevelMaker::~LevelMaker()
{
	delete ui;
}

void LevelMaker::on_MainMenuButton_clicked()
{
	emit MainMenuButton_clicked();
}
