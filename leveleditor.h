#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H


#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

#include "level.h"
#include "tile.h"

class LevelEditor: public QGraphicsView{
	Q_OBJECT
public:
	LevelEditor(QString levelname, QWidget *parent=0);

private:
	QGraphicsScene *scene;
	Level *level;
	QString levelname;
	Type drawmode = empty;

	void saveLevel();
	int getSelectorPos();

	void keyPressEvent(QKeyEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;

signals:
	void MainMenuButton_clicked();


private slots:
	void on_MainMenuButton_clicked();


};

#endif // LEVELEDITOR_H
