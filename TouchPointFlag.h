#ifndef TOUCHPOINTFLAG_H
#define TOUCHPOINTFLAG_H

#include "BaseCtrl.h"
#include "ui_qfrontwindow.h"
#include <QWidget>
#include <QPainter>

class TouchPointFlag : public BaseCtrl
{
	Q_OBJECT
public:
	TouchPointFlag(QWidget *parent);
	~TouchPointFlag();

	void Draw();
	void Refresh();

	int m_radius;		//Բ�뾶

	//
	QRectF m_showSection;
	void SetRadius(int x);

private:
	Ui::QFrontWindow ui;
};

#endif