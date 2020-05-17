#ifndef ARROW_H
#define ARROW_H

#include "BaseCtrl.h"
#include <QVector>
#include <qpoint.h>

class Arrow : public BaseCtrl
{
	Q_OBJECT
public:
	Arrow(QWidget *parent);
	~Arrow();

	QVector<QPoint> m_vectorArrow;

	void Draw();
	void Refresh();

	float m_alpha;
	float m_length;
	float m_startPos;

	void SetAlpha(float alpha);
	void SetLength(float length);
	void SetStartPos(float pos);
};

#endif