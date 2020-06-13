#ifndef LEVELMAKER_H
#define LEVELMAKER_H

#define WIDTH 30
#define HEIGHT 20

#include <QWidget>

namespace Ui {
class LevelMaker;
}

class LevelMaker : public QWidget
{
	Q_OBJECT

public:
	explicit LevelMaker(QWidget *parent = nullptr);
	~LevelMaker();

private:
	Ui::LevelMaker *ui;
	QWidget *subscreen;

	void openEditor(QString lvlname);
	void makeEmptyLevel(QString lvlname);
	void newSubScreen(QWidget *ss);

signals:
	void MainMenuButton_clicked();

private slots:
	void on_MainMenuButton_clicked();
	void on_NewButton_clicked();
	void toFirstPage();
};

#endif // LEVELMAKER_H
