#ifndef MAPMARKPOINT2_H
#define MAPMARKPOINT2_H

#include "BaseCtrl.h"
#include <QWidget>

#define MAPMARKPOINT2_RADIUS_1 (25)
#define MAPMARKPOINT2_RADIUS_2 (13)
#define MAPMARKPOINT2_BORDER (4)

class MapMarkPoint2 : public BaseCtrl
{
	Q_OBJECT
public:
	MapMarkPoint2(QWidget *parent);
	~MapMarkPoint2();

	void Draw();
	void Refresh();

	//���Ƽ�������
	int m_selectedIndex;

	//���η�Χ
	QVector<QPoint> m_vector;

	//�ؼ���λ��
	QPointF m_point;


	//��ʾ����
	QRectF m_showSection1;
	QRectF m_showSection2;

	//��������
	QRectF m_ctrlSection1;
	QRectF m_ctrlSection2;

	//�������Ըı�ӿ�
	int OnPress(QPointF point);
	int OnRelease(QPointF point);
	int OnMove(QPointF prePoint, QPointF postPoint);
	int OnClick(QPointF point);

signals:
	void sigDrag(QPointF, QPointF);

private:
	//
	float Square(const double num);									//��ƽ��
	float TwoPtDistance(const QPointF &pt1, const QPointF &pt2);	//��������

	//
	QImage *m_pImage;
};


#endif