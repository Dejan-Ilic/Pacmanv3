#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>

namespace Ui {
class GameOver;
}

class GameOver : public QWidget
{
	Q_OBJECT

public:
	explicit GameOver(QWidget *parent = nullptr);
	~GameOver();

private:
	Ui::GameOver *ui;

signals:
	void MainMenuButton_clicked();


private slots:
	void on_MainMenuButton_clicked();
};

#endif // GAMEOVER_H
