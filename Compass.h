#ifndef COMPASS_H
#define COMPASS_H

#include "BaseCtrl.h"
#include <QWidget>

#define COMPASS_RADIUS (40)
#define QCOMPASS_DEFAULT_IMAGE_PATH ("Resource/Map/campass.png")
#define QCOMPASS_PRESSED_IMAGE_PATH ("Resource/Map/campass_pressed.png")

class Compass : public BaseCtrl
{
	Q_OBJECT
public:
	Compass(QWidget *parent);
	~Compass();

	int m_state;

	float m_alpha;
	void SetAlpha(float alpha);

	void Draw();
	void Refresh();

	QRectF m_showSection;
	QRectF m_showSectionInter;

	QImage *m_pImage;
	QImage *m_pImageInter;
	QImage *m_pImagePressed;

	int IsInSection(QPointF point);

	int OnPress(QPointF point);
	int OnRelease(QPointF point);
	int OnMove(QPointF pointOld, QPointF pointNew);

signals:
	void sigResetAlpha();
};

#endif