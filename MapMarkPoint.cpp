#include "MapMarkPoint.h"
#include <qpainter.h>
#include <qmath.h>
#include <qdebug.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

MapMarkPoint::MapMarkPoint(QWidget *parent)
	: BaseCtrl(parent)
{
	m_selectedIndex = 0;

	m_pImage = new QImage("Resource/FanShaped/page-1-icon-control-heading.png");
}

MapMarkPoint::~MapMarkPoint()
{
	if (m_pImage != NULL)
		delete m_pImage;
}


int MapMarkPoint::OnClick(QPointF point)
{
	if (IsInCtrlSection(m_ctrlSection2, point))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int MapMarkPoint::OnPress(QPointF point)
{
	if (IsInCtrlSection(m_ctrlSection2, point))
	{
		m_selectedIndex = 1;
	}

	if (m_selectedIndex != 0)
	{
		//qDebug() << m_selectedIndex;
		return 1;
	}
	else
	{
		//qDebug() << m_selectedIndex;
		return 0;
	}
}

int MapMarkPoint::OnRelease(QPointF point)
{
	if (m_selectedIndex != 0)
	{
		switch (m_selectedIndex)
		{
		default:
			break;
		}
		m_selectedIndex = 0;
		return 1;
	}
	else
		return 0;
}

int MapMarkPoint::OnMove(QPointF prePoint, QPointF postPoint)
{
	if (m_selectedIndex == 1)
	{
		emit sigDrag(prePoint, postPoint);
		return 1;
	}
	return 0;
}

void MapMarkPoint::Refresh()
{
	QPoint tempPoint;

	m_point.setX(m_x);
	m_point.setY(m_y);

	m_showSection1.setRect(m_point.x() - MAPMARKPOINT_RADIUS_1, m_point.y() - MAPMARKPOINT_RADIUS_1, 2 * MAPMARKPOINT_RADIUS_1, 2 * MAPMARKPOINT_RADIUS_1);
	m_ctrlSection1 = m_showSection1;

	m_showSection2.setRect(m_point.x() - MAPMARKPOINT_RADIUS_2, m_point.y() - MAPMARKPOINT_RADIUS_2, 2 * MAPMARKPOINT_RADIUS_2, 2 * MAPMARKPOINT_RADIUS_2);
	m_ctrlSection2 = m_showSection2;
}

//����
void MapMarkPoint::Draw()
{
	QPen pen;
	QFont font;
	QBrush brush;
	QPainter painter;
	QRectF tempRect;
	float tempAngle;
	QString tempStr;
	QPointF tempPoint;

	//�������Ч�����ķ���
	if (m_isShow == false)
		return;

	//��ʼ
	painter.begin(m_parent);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

	//����
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(252, 138, 0, 153));
	painter.drawEllipse(m_showSection1);

	pen.setWidth(4);
	pen.setColor(QColor(255, 255, 255, 255));
	painter.setPen(pen);
	painter.setBrush(QColor(252, 138, 0, 255));
	painter.drawEllipse(m_showSection2);

	//����
	painter.end();
}

//��ƽ��
float MapMarkPoint::Square(const double num)
{
	return num*num;
}

//��������
float MapMarkPoint::TwoPtDistance(const QPointF &pt1, const QPointF &pt2)
{
	return sqrt(Square(pt2.x() - pt1.x()) + Square(pt2.y() - pt1.y()));
}