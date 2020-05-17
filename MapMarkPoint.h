#ifndef MAPMARKPOINT_H
#define MAPMARKPOINT_H

#include "BaseCtrl.h"
#include <QWidget>

#define MAPMARKPOINT_RADIUS_1 (25)
#define MAPMARKPOINT_RADIUS_2 (13)
#define MAPMARKPOINT_BORDER (4)

class MapMarkPoint : public BaseCtrl
{
	Q_OBJECT
public:
	MapMarkPoint(QWidget *parent);
	~MapMarkPoint();

	void Draw();
	void Refresh();

	//控制激活区域
	int m_selectedIndex;

	//扇形范围
	QVector<QPoint> m_vector;

	//关键点位置
	QPointF m_point;


	//显示区域
	QRectF m_showSection1;
	QRectF m_showSection2;

	//控制区域
	QRectF m_ctrlSection1;
	QRectF m_ctrlSection2;

	//扇面属性改变接口
	int OnPress(QPointF point);
	int OnRelease(QPointF point);
	int OnMove(QPointF prePoint, QPointF postPoint);
	int OnClick(QPointF point);

signals:
	void sigDrag(QPointF, QPointF);

private:
	//
	float Square(const double num);									//求平方
	float TwoPtDistance(const QPointF &pt1, const QPointF &pt2);	//两点间距离

	//
	QImage *m_pImage;
};


#endif