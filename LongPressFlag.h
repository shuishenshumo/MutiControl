#ifndef LONGPRESSFLAG_H
#define LONGPRESSFLAG_H

#include "BaseCtrl.h"
#include <QWidget>

class LongPressFlag : public BaseCtrl
{
	Q_OBJECT
public:
	LongPressFlag(QWidget *parent);
	~LongPressFlag();
	
	void Draw();
	void Refresh();

	int m_radius;		//Բ�뾶
	float m_percent;	//

	//
	QRectF m_showSection;
	void SetKeyPoint(int x, int y);
	void SetRadius(int x);
	void SetPercent(float percent);
};

#endif