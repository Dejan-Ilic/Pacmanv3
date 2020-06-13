#ifndef LEVELMAKER_H
#define LEVELMAKER_H

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
	void toFirstPage();

signals:
	void MainMenuButton_clicked();


private slots:
	void on_MainMenuButton_clicked();
	void on_NewButton_clicked();
};

#endif // LEVELMAKER_H
