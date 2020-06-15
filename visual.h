#ifndef VISUAL_H
#define VISUAL_H

#include <QGraphicsRectItem>
#include <QObject>

#include "vec.h"
#include "idx.h"



class Visual: public QObject, public QGraphicsPixmapItem{
	Q_OBJECT
public:
	Visual();

	//handy helper function
	static Vec getScreenPos(int i, int j);
	static Vec getScreenPos(Idx v);
	static Vec getCenteredScreenPos(int i, int j);
	static Vec getCenteredScreenPos(Idx v);

	Idx getIdx();

	//essentials, have to be overridded
	virtual void setPos_ij(int i, int j) = 0;
	virtual void setPos_ij(Idx v) = 0;

	//omdat qT de oorsprong niet naar het midden van de sprite wilt verplaatsen...
	virtual int getCenterX() const = 0;
	virtual int getCenterY() const = 0;
	virtual Vec getCenterPos() const = 0;
};

#endif // VISUAL_H
