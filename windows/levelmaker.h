#ifndef LEVELMAKER_H
#define LEVELMAKER_H

#include "util/constants.h"

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

	void newSubScreen(QWidget *ss);
	void updateLists();
	void saveLevelOrder();

signals:
	void MainMenuButton_clicked();

private slots:
	void on_MainMenuButton_clicked();
	void on_EditButton_clicked();
	void toFirstPage();

	void on_SelectButton_clicked();
	void on_DeleteButton_clicked();
	void on_DeselectButton_clicked();
	void on_UpButton_clicked();
	void on_DownButton_clicked();
	void on_RenameButton_clicked();
	void on_CopyButton_clicked();
};

#endif // LEVELMAKER_H
