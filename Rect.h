#ifndef RECT_H
#define RECT_H

#include "BaseCtrl.h"
#include <QVector>
#include <qpoint.h>

class Rect : public BaseCtrl
{
	
	Q_OBJECT
public:
	Rect(QWidget *parent);
	~Rect();

	int m_width;
	int m_height;

	void Draw();
	void FrameInit();

	void Refresh();

	void SetWidth(int width);
	void SetHeight(int height);

public slots:
void readFrame();

};

#endif