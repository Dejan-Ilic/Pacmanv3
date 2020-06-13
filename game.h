#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

class Game: public QGraphicsView{
	Q_OBJECT
public:
	Game(QWidget *parent=0);

private:
	QGraphicsScene *scene;
	void keyPressEvent(QKeyEvent *event) override;

signals:
	void MainMenuButton_clicked();


private slots:
	void on_MainMenuButton_clicked();

};

#endif // GAME_H
