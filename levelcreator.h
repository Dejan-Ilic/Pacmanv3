#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

class LevelCreator: public QGraphicsView{
	Q_OBJECT
public:
	LevelCreator(QWidget *parent=0);

private:
	QGraphicsScene *scene;
	void keyPressEvent(QKeyEvent *event) override;

signals:
	void backToLevelMaker();


private slots:
	void on_backToLevelMaker();


};

#endif // LEVELCREATOR_H
