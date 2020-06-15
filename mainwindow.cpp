#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "levelmaker.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	subscreen = nullptr;
	setWindowTitle("PACMAN - DEJAN ILIC");
	setFixedSize(800, 600);
}

MainWindow::~MainWindow(){
	delete ui;
	if(subscreen != nullptr)
		delete subscreen;
}

void MainWindow::newSubScreen(QWidget *ss){
	subscreen = ss;
	ui->stackedWidget->addWidget(subscreen);
	connect(subscreen, SIGNAL(MainMenuButton_clicked()), this, SLOT(toFirstPage()));

	ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::toFirstPage(){
	ui->stackedWidget->setCurrentIndex(0);
	ui->stackedWidget->removeWidget(subscreen);
	delete subscreen;
	subscreen = nullptr;
}



void MainWindow::on_GameButton_clicked(){
	newSubScreen(new Game());
}

void MainWindow::on_LevelMakerButton_clicked(){
	newSubScreen(new LevelMaker());
}

