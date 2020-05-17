#ifndef LOCATION_H
#define LOCATION_H

#include "BaseCtrl.h"
#include <QWidget>

#define LOCATION_RADIUS (40)
#define LOCATION_DEFAULT_IMAGE_PATH ("Resource/Map/location.png")
#define LOCATION_PRESSED_IMAGE_PATH ("Resource/Map/location_pressed.png")

class Location : public BaseCtrl
{
	Q_OBJECT
public:
	Location(QWidget *parent);
	~Location();

	int m_state;

	void Draw();
	void Refresh();

	QRectF m_showSection;

	QImage *m_pImage;
	QImage *m_pImagePressed;

	int IsInSection(QPointF point);

	int OnPress(QPointF point);
	int OnRelease(QPointF point);
	int OnMove(QPointF pointOld, QPointF pointNew);

signals:
	void sigResetLocation();
};

#endif