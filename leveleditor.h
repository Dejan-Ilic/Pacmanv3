#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H


#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

class LevelEditor: public QGraphicsView{
	Q_OBJECT
public:
	LevelEditor(QWidget *parent=0);

private:
	QGraphicsScene *scene;
	void keyPressEvent(QKeyEvent *event) override;

signals:
	void MainMenuButton_clicked();


private slots:
	void on_MainMenuButton_clicked();


};

#endif // LEVELEDITOR_H
