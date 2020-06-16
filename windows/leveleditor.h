#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H


#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QBrush>
#include <Qt>

#include "gameLogic/level.h"
#include "gameItems/tile.h"
#include "util/vec.h"


class LevelEditor: public QGraphicsView{
	Q_OBJECT
public:
	LevelEditor(QString levelname, QWidget *parent=0);
	~LevelEditor();

private:
	QGraphicsScene *scene;
	Level *level;
	QString levelname;
	Type drawmode = empty;

	QGraphicsSimpleTextItem *quit;
	static const int Nlabels = 10;
	QGraphicsSimpleTextItem *label[Nlabels];

	static const Vec labelpos[Nlabels];
	static const QString caption[Nlabels];
	static const Type drawtype[Nlabels];

	const QBrush unselected;
	const QBrush selected;

	void saveLevel();
	int getButtonIdx(Type t);
	void switchMode(Type t);

	void keyPressEvent(QKeyEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

signals:
	void MainMenuButton_clicked();


private slots:
	void on_MainMenuButton_clicked();


};

#endif // LEVELEDITOR_H
