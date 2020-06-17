#ifndef VISUAL_H
#define VISUAL_H

#include <QGraphicsRectItem>
#include <QObject>

#include "util/vec.h"
#include "util/idx.h"



class Visual: public QObject, public QGraphicsPixmapItem{
	Q_OBJECT
public:
	Visual();

	//handy helper function
	static Vec idxToVec(int i, int j);
	static Vec idxToVec(Idx v);
	static Vec idxToCenteredVec(int i, int j);
	static Vec idxToCenteredVec(Idx v);

	static Idx vecToIdx(int x, int y);
	static Idx vecToIdx(Vec v);
	static Idx centeredVecToIdx(int x, int y);
	static Idx centeredVecToIdx(Vec v);


	Idx getIdx() const;

	//essentials, have to be overridded
	virtual void setPos_ij(int i, int j) = 0;
	virtual void setPos_ij(Idx v) = 0;

	//omdat qT de oorsprong niet naar het midden van de sprite wilt verplaatsen...
	virtual int getCenterX() const = 0;
	virtual int getCenterY() const = 0;
	virtual Vec getCenterPos() const = 0;
};

#endif // VISUAL_H
