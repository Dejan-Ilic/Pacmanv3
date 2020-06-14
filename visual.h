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

	//essentials, have to be overridded
	virtual void setPos_ij(int i, int j) = 0;
	virtual void setPos_ij(Idx v) = 0;
};

#endif // VISUAL_H
