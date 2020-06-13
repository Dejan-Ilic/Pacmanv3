#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "levelmaker.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow(){
	delete ui;
}


void MainWindow::on_GameButton_clicked(){
	subscreen = new Game();
	ui->stackedWidget->addWidget(subscreen);
	connect(subscreen, SIGNAL(MainMenuButton_clicked()), this, SLOT(toMainMenu()));

	ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_LevelMakerButton_clicked(){
	subscreen = new LevelMaker();
	ui->stackedWidget->addWidget(subscreen);
	connect(subscreen, SIGNAL(MainMenuButton_clicked()), this, SLOT(toMainMenu()));


	ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::toMainMenu(){
	ui->stackedWidget->setCurrentIndex(0);


	ui->stackedWidget->removeWidget(subscreen);
	delete subscreen;

}
