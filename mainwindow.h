#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_GameButton_clicked();
	void on_LevelMakerButton_clicked();
	void toMainMenu();

private:
	Ui::MainWindow *ui;
	QWidget *subscreen;
};
#endif // MAINWINDOW_H
