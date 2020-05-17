#include "FanShapedSection.h"
#include <qpainter.h>
#include <qmath.h>
#include <qdebug.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

FanShapedSection::FanShapedSection(QWidget *parent)
	: BaseCtrl(parent)
{
	m_selectedIndex = 0;

	m_startAngle = 0;
	m_spanAngle = 0;
	m_radius = 0;
	m_direction = -1;	//Ĭ��˳ʱ������
	m_cutNum = 3;

	m_piasAngle = 0;

	m_pImageHeading = new QImage("Resource/FanShaped/page-1-icon-control-heading.png");
	m_pImageAngle = new QImage("Resource/FanShaped/page-1-icon-control-angle.png");
	m_pImageRadius = new QImage("Resource/FanShaped/page-1-icon-control-�뾶.png");
	m_pImageDirection1 = new QImage("Resource/FanShaped/page-1-icon-control-��ʼת��.png");		//˳ʱ��
	m_pImageDirection2 = new QImage("Resource/FanShaped/page-1-icon-control-��ʼת��-copy.png");	//��ʱ��
	m_pImageAdd = new QImage("Resource/FanShaped/page-1-icon-control-����-.png");
	m_pImageMinus = new QImage("Resource/FanShaped/page-1-icon-control-����-.png");

	m_arrow1 = new Arrow(m_parent);
	m_arrow2 = new Arrow(m_parent);
}

FanShapedSection::~FanShapedSection()
{
	if (m_pImageHeading != NULL)
		delete m_pImageHeading;
	if (m_pImageAngle != NULL)
		delete m_pImageAngle;
	if (m_pImageRadius != NULL)
		delete m_pImageRadius;
	if (m_pImageDirection1 != NULL)
		delete m_pImageDirection1;
	if (m_pImageDirection2 != NULL)
		delete m_pImageDirection2;
	if (m_pImageAdd != NULL)
		delete m_pImageAdd;
	if (m_pImageMinus != NULL)
		delete m_pImageMinus;
	if (m_arrow1 != NULL)
		delete m_arrow1;
	if (m_arrow2 != NULL)
		delete m_arrow2;
}

void FanShapedSection::SetShowType(int type)
{
	m_showType = type;
}

void FanShapedSection::SetStartAngle(float angle)
{
	m_startAngle = angle;
}

void FanShapedSection::SetSpanAngle(float angle)
{
	m_spanAngle = angle;
}

void FanShapedSection::SetRadius(float radius)
{
	m_radius = radius;
}

void FanShapedSection::SetDirection(int direction)
{
	m_direction = direction;
}

void FanShapedSection::SetCutNum(int num)
{
	m_cutNum = num;
}

void FanShapedSection::SetDis(float dis)
{
	m_dis = dis;
}

void FanShapedSection::SetPiasAngle(float angle)
{
	m_piasAngle = angle;
}

float FanShapedSection::GetDis()
{
	return m_dis;
}

float FanShapedSection::GetRadius()
{
	return m_radius;
}

float FanShapedSection::GetPiasAngle()
{
	return m_piasAngle;
}

void FanShapedSection::AdjustStartAngle(float anglePias)
{
	emit sigAdjustStartAngle(anglePias);
}

void FanShapedSection::AdjustSpanAngle(float anglePias)
{
	emit sigAdjustSpanAngle(anglePias);
}

void FanShapedSection::AdjustRadius(float radiusPias)
{
	m_bIsRadiusChanged = true;

	emit sigAdjustRadius(radiusPias);
}

void FanShapedSection::AdjustDis(float disPias)
{

}

bool FanShapedSection::IsRefreshDis()
{
	return m_bIsRadiusChanged;
}

void FanShapedSection::HasRefreshedDis()
{
	m_bIsRadiusChanged = false;
}

void FanShapedSection::ReversalDirection()
{
	emit sigReversalDirection();
}

int FanShapedSection::IsInFanShapedSection(QPointF point)
{
	QPolygon polygon(m_vector);
	QPoint tempPoint;

	tempPoint.setX(point.x());
	tempPoint.setY(point.y());
	if (polygon.containsPoint(tempPoint, Qt::OddEvenFill) == 1)
		return 1;
	else
		return 0;

	//if (sqrt(point.x() * point.x() + point.y() * point.y()) < m_radius)
	//	return 1;
	//else
	//	return 0;
}

int FanShapedSection::OnAddNum()
{
	if (m_cutNum < 10)
	{
		m_cutNum++;
		if (m_spanAngle > 360.0 / m_cutNum)
			m_spanAngle = 360.0 / m_cutNum;
		return 1;
	}
	else
	{
		return 0;
	}
}

int FanShapedSection::OnMinusNum()
{
	if (m_cutNum > 2)
	{
		m_cutNum--;
		return 1;
	}
	else
	{
		return 0;
	}
}

int FanShapedSection::OnZoom(QPointF point, float delta)
{
	SetRadius(m_radius * delta);
	return 1;
}

int FanShapedSection::OnRotate(QPointF point, float alpha)
{
	AdjustStartAngle(alpha);
	return 1;
}

int FanShapedSection::OnPress(QPointF point)
{
	if (IsInCtrlSection(m_ctrlSectionAngle, point))
	{
		m_selectedIndex = 2;
		m_point = point;
	}
	else if (IsInCtrlSection(m_ctrlSectionRadius, point))
	{
		m_selectedIndex = 3;
		m_point = point;
	}
	else if (IsInCtrlSection(m_ctrlSectionAzimuth, point))
	{
		m_selectedIndex = 1;
		m_point = point;
	}
#if 0
	else if (IsInCtrlSection(m_ctrlSectionAddNum, point))
	{
		m_selectedIndex = 4;
	}
	else if (IsInCtrlSection(m_ctrlSectionMinusNum, point))
	{
		m_selectedIndex = 5;
	}
#endif
	else if (IsInCtrlSection(m_ctrlSectionDirection, point))
	{
		m_selectedIndex = 6;
	}
	else if (IsInCtrlSection(m_ctrlSectionDrag, point) || IsInFanShapedSection(point))
	{
		m_selectedIndex = 7;
	}

	if (m_selectedIndex != 0)
	{
		qDebug() << m_selectedIndex;
		return 1;
	}
	else
	{
		qDebug() << m_selectedIndex;
		return 0;
	}
}

int FanShapedSection::OnRelease(QPointF point)
{
	if (m_selectedIndex != 0)
	{
		switch (m_selectedIndex)
		{
#if 0
		case 4:
			OnAddNum();
			break;
		case 5:
			OnMinusNum();
			break;
#endif
		case 6:
			if (IsInCtrlSection(m_ctrlSectionDirection, point))
			{
				ReversalDirection();
			}
			break;
		default:
			break;
		}
		m_selectedIndex = 0;
		return 1;
	}else
		return 0;
}

//���ض���
int FanShapedSection::OnMove(QPointF oldPoint, QPointF newPoint)
{
	QLineF line1(QPointF(m_x, m_y), oldPoint);
	QLineF line2(QPointF(m_x, m_y), newPoint);
	float alpha = 0;
	float delta = 0;

	//�Ƕȱ仯��
	alpha = line2.angleTo(line1);
	if (alpha > 180)
		alpha = 360 - alpha;
	else
		alpha = -1 * alpha;

	//����仯��
	delta = line2.length() - line1.length();

	//���ձ�ѡ�����Ĳ�ͬ��ִ�в�ͬ�Ķ���
	if (m_selectedIndex == 2)
	{		
		AdjustSpanAngle(alpha);
		m_point = newPoint;
		return 1;
	}
	else if (m_selectedIndex == 3)
	{
		AdjustRadius(delta);
		m_point = newPoint;
		return 1;
	}
	else if (m_selectedIndex == 1)
	{
		AdjustStartAngle(alpha);
		m_point = newPoint;
		return 1;
	}
	else if (m_selectedIndex == 7)
	{
		emit sigDrag(oldPoint, newPoint);
		//AdjustKeyPoint(newPoint.x() - oldPoint.x(), newPoint.y() - oldPoint.y());
		return 1;
	}
	else if (m_selectedIndex == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void FanShapedSection::Refresh()
{
	QPoint tempPoint;
	float tempAngle;

	tempAngle = 45;

	//�����Ƶ�
	float radiusPlus = 0 + CONCENTRIC_CIRCLE_PIAS;

	//����
	m_pointAzimuth.setX(m_x + radiusPlus * cos(tempAngle / 360 * 2 * M_PI));
	m_pointAzimuth.setY(m_y - radiusPlus * sin(tempAngle / 360 * 2 * M_PI));
	m_showSectionAzimuth.setRect(m_pointAzimuth.x() - BIG_SECTION, m_pointAzimuth.y() - BIG_SECTION, 2 * BIG_SECTION, 2 * BIG_SECTION);
	m_ctrlSectionAzimuth = m_showSectionAzimuth.marginsAdded(QMarginsF(TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE));

	//�����
	m_pointAngle.setX(m_x + radiusPlus*cos((tempAngle - ANGLE_PIAS) / 360 * 2 * M_PI));
	m_pointAngle.setY(m_y - radiusPlus*sin((tempAngle - ANGLE_PIAS) / 360 * 2 * M_PI));
	m_showSectionAngle.setRect(m_pointAngle.x() - BIG_SECTION, m_pointAngle.y() - BIG_SECTION, 2 * BIG_SECTION, 2 * BIG_SECTION);
	m_ctrlSectionAngle = m_showSectionAngle.marginsAdded(QMarginsF(TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE));

	//�뾶
	m_pointRadius.setX(m_x + radiusPlus*cos((tempAngle - 2 * ANGLE_PIAS) / 360 * 2 * M_PI));
	m_pointRadius.setY(m_y - radiusPlus*sin((tempAngle - 2 * ANGLE_PIAS) / 360 * 2 * M_PI));
	m_showSectionRadius.setRect(m_pointRadius.x() - BIG_SECTION, m_pointRadius.y() - BIG_SECTION, 2 * BIG_SECTION, 2 * BIG_SECTION);
	m_ctrlSectionRadius = m_showSectionRadius.marginsAdded(QMarginsF(TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE));

	//˳����ʱ��
	m_pointDirection.setX(m_x + radiusPlus*cos((tempAngle - 3 * ANGLE_PIAS) / 360 * 2 * M_PI));
	m_pointDirection.setY(m_y - radiusPlus*sin((tempAngle - 3 * ANGLE_PIAS) / 360 * 2 * M_PI));
	m_showSectionDirection.setRect(m_pointDirection.x() - BIG_SECTION, m_pointDirection.y() - BIG_SECTION, 2 * BIG_SECTION, 2 * BIG_SECTION);
	m_ctrlSectionDirection = m_showSectionDirection.marginsAdded(QMarginsF(TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE));

	//������������
	m_pointAddNum.setX(m_x + radiusPlus*cos((tempAngle - 4 * ANGLE_PIAS) / 360 * 2 * M_PI));
	m_pointAddNum.setY(m_y - radiusPlus*sin((tempAngle - 4 * ANGLE_PIAS) / 360 * 2 * M_PI));
	m_showSectionAddNum.setRect(m_pointAddNum.x() - BIG_SECTION, m_pointAddNum.y() - BIG_SECTION, 2 * BIG_SECTION, 2 * BIG_SECTION);
	m_ctrlSectionAddNum = m_showSectionAddNum.marginsAdded(QMarginsF(TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE));

	//������������
	m_pointMinusNum.setX(m_x + radiusPlus*cos((tempAngle - 5 * ANGLE_PIAS) / 360 * 2 * M_PI));
	m_pointMinusNum.setY(m_y - radiusPlus*sin((tempAngle - 5 * ANGLE_PIAS) / 360 * 2 * M_PI));
	m_showSectionMinusNum.setRect(m_pointMinusNum.x() - BIG_SECTION, m_pointMinusNum.y() - BIG_SECTION, 2 * BIG_SECTION, 2 * BIG_SECTION);
	m_ctrlSectionMinusNum = m_showSectionMinusNum.marginsAdded(QMarginsF(TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE));

	//������ק
	m_pointDrag.setX(m_x);
	m_pointDrag.setY(m_y);
	m_showSectionDrag.setRect(m_pointDrag.x() - m_radius - DRAG_CIRCLE_RADIUS, m_pointDrag.y() - m_radius - DRAG_CIRCLE_RADIUS, 2 * (m_radius + DRAG_CIRCLE_RADIUS), 2 * (m_radius+DRAG_CIRCLE_RADIUS));
	m_ctrlSectionDrag = m_showSectionDrag.marginsAdded(QMarginsF(TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE, TOUCH_COMPENSATE));

	//
	tempAngle = -m_startAngle + 90 - m_piasAngle;
	m_vector.clear();

	float leftAngle = 0, rightAngle = 0;
	int tempDir = 1;

	leftAngle = tempAngle - 180;
	rightAngle = tempAngle;

	while(1)
	{
		//�ж����λ��ƽ���
		if (m_direction == -1)
		{
			if ((leftAngle < (tempAngle - 360 + 5) || rightAngle < (tempAngle - 180 + 5)))
				break;
		}
		else
		{
			if ((leftAngle > (tempAngle - 5) || rightAngle > (tempAngle + 180 - 5)))
				break;
		}

		//����ͼ�λ���
		if (tempDir == 1)
		{
			tempPoint.setX(m_x + m_radius*cos(leftAngle / 360 * 2 * M_PI));
			tempPoint.setY(m_y - m_radius*sin(leftAngle / 360 * 2 * M_PI));
			m_vector.append(tempPoint);

			tempPoint.setX(m_x + m_radius*cos(rightAngle / 360 * 2 * M_PI));
			tempPoint.setY(m_y - m_radius*sin(rightAngle / 360 * 2 * M_PI));
			m_vector.append(tempPoint);
		}else
		{
			tempPoint.setX(m_x + m_radius*cos(rightAngle / 360 * 2 * M_PI));
			tempPoint.setY(m_y - m_radius*sin(rightAngle / 360 * 2 * M_PI));
			m_vector.append(tempPoint);

			tempPoint.setX(m_x + m_radius*cos(leftAngle / 360 * 2 * M_PI));
			tempPoint.setY(m_y - m_radius*sin(leftAngle / 360 * 2 * M_PI));
			m_vector.append(tempPoint);
		}

		//���ݻ��Ʒ���ѡ��Ƕȱ仯����
		if (m_direction == -1)
		{
			leftAngle -= m_spanAngle;
			rightAngle -= m_spanAngle;
		}
		else
		{
			leftAngle += m_spanAngle;
			rightAngle += m_spanAngle;
		}

		tempDir = (tempDir + 1) % 2;
	}

#if 0
	for (int i = 0; i < m_cutNum; i++)
	{
		tempAngle = tempAngle + m_direction * 360.0 / m_cutNum;

		tempPoint.setX(m_x);
		tempPoint.setY(m_y);
		m_vector.append(tempPoint);

		tempPoint.setX(m_x + m_radius*cos(tempAngle / 360 * 2 * M_PI));
		tempPoint.setY(m_y - m_radius*sin(tempAngle / 360 * 2 * M_PI));
		m_vector.append(tempPoint);

		tempPoint.setX(m_x + m_radius*cos((tempAngle + m_direction * m_spanAngle) / 360 * 2 * M_PI));
		tempPoint.setY(m_y - m_radius*sin((tempAngle + m_direction * m_spanAngle) / 360 * 2 * M_PI));
		m_vector.append(tempPoint);

		tempPoint.setX(m_x);
		tempPoint.setY(m_y);
		m_vector.append(tempPoint);
	}
#endif

	//
	m_vectorArrow1.clear();
	m_vectorArrow1.append(QPoint(m_x, m_y - 1.3*m_radius));
	m_vectorArrow1.append(QPoint(m_x - 10, m_y - 1.3*m_radius + 20));
	m_vectorArrow1.append(QPoint(m_x + 10, m_y - 1.3*m_radius + 20));
	m_vectorArrow1.append(QPoint(m_x, m_y - 1.3*m_radius));

	m_vectorArrow2.clear();
	m_vectorArrow2.append(QPoint(0, 0 - 1.3*m_radius));
	m_vectorArrow2.append(QPoint(0 - 10, 0 - 1.3*m_radius + 20));
	m_vectorArrow2.append(QPoint(0 + 10, 0 - 1.3*m_radius + 20));
	m_vectorArrow2.append(QPoint(0, 0 - 1.3*m_radius));

	//
	QLineF line1(QPointF(m_x, m_y), m_point);
	QLineF line2(QPointF(m_x, m_y), QPointF(m_x, m_y - 100));
	float alpha = line1.angleTo(line2);

	if (m_selectedIndex == 1 || m_selectedIndex == 2)
	{
		//��ת

		m_arrow1->SetShow(true);
		m_arrow2->SetShow(true);

		m_arrow1->SetKeyPoint(m_point.x(), m_point.y());
		m_arrow1->SetAlpha(alpha - 90);

		m_arrow2->SetKeyPoint(m_point.x(), m_point.y());
		m_arrow2->SetAlpha(alpha + 90);
	}
	else if (m_selectedIndex == 3)
	{
		//����

		m_arrow1->SetShow(true);
		m_arrow2->SetShow(true);

		m_arrow1->SetKeyPoint(m_point.x(), m_point.y());
		m_arrow1->SetAlpha(alpha);

		m_arrow2->SetKeyPoint(m_point.x(), m_point.y());
		m_arrow2->SetAlpha(alpha - 180);
	}
	else
	{
		m_arrow1->SetShow(false);
		m_arrow2->SetShow(false);
	}
}

//����
void FanShapedSection::Draw()
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
	if (m_isShow == false || m_spanAngle == 0 || m_radius == 0)
		return;

	//��ʼ
	painter.begin(m_parent);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

	//����
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(42, 42, 42, 102));
	painter.drawEllipse(m_showSectionDrag);

	//����������
	pen.setColor(QColor(255, 140, 0, 255));
	pen.setWidth(6);
	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	painter.setPen(pen);

	//������
	//painter.setBrush(QColor(255, 140, 0, 50));
	//painter.drawPolygon(QPolygon(m_vector));
	
	//painter.setBrush(Qt::NoBrush);
	//painter.drawPolygon(QPolygon(m_vector));
	
	//������������·��
	for (int i = 0; i < m_vector.length() - 1; i++)
	{
#if 0
		QRadialGradient gradient;
		gradient.setColorAt(0, QColor(255 * i / m_vector.length(), 140, 0, 255));
		gradient.setColorAt(1, QColor(255 * (i+1) / m_vector.length(), 140, 0, 255));
		pen.setBrush(gradient);
		painter.setPen(pen);
#endif
		painter.drawLine(m_vector.at(i), m_vector.at(i+1));
	}
	
	//ͻ�Ե�ǰ��ѡ��Ŀ���Ԫ��
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(255, 140, 0, 255));
	switch(m_selectedIndex)
	{
	case 1:
		painter.drawEllipse(m_showSectionAzimuth);
		break;
	case 2:
		painter.drawEllipse(m_showSectionAngle);
		break;
	case 3:
		painter.drawEllipse(m_showSectionRadius);
		break;
	case 4:
		painter.drawEllipse(m_showSectionAddNum);
		break;
	case 5:
		painter.drawEllipse(m_showSectionMinusNum);
		break;
	case 6:
		painter.drawEllipse(m_showSectionDirection);
		break;
	case 7:
		painter.setBrush(QColor(255, 140, 0, 50));
		painter.drawEllipse(m_ctrlSectionDrag);
		break;
	default:
		break;
	}

	//����Ԫ��
	painter.drawImage(m_showSectionAzimuth, *m_pImageHeading);
	painter.drawImage(m_showSectionAngle, *m_pImageAngle);
	painter.drawImage(m_showSectionRadius, *m_pImageRadius);
	if (m_direction == -1)
		painter.drawImage(m_showSectionDirection, *m_pImageDirection1);		//˳ʱ��
	else
		painter.drawImage(m_showSectionDirection, *m_pImageDirection2);		//��ʱ��
#if 0
	painter.drawImage(m_showSectionAddNum, *m_pImageAdd);
	painter.drawImage(m_showSectionMinusNum, *m_pImageMinus);
#endif

	//��������
	pen.setColor(QColor(255, 140, 0, 255));
	painter.setPen(pen);
	font.setFamily("����");
	font.setPixelSize(36);
	painter.setFont(font);

	//��ʼ����Ƕ�
	tempStr.sprintf("%.0f��", m_startAngle);
	painter.drawText(QRectF(m_pointAzimuth.x() + BIG_SECTION + 10, m_pointAzimuth.y(), 400, 400), Qt::AlignLeft | Qt::AlignTop, tempStr);
	
	//�����
	tempStr.sprintf("%.0f��", m_spanAngle);
	painter.drawText(QRectF(m_pointAngle.x() + BIG_SECTION + 10, m_pointAngle.y(), 400, 400), Qt::AlignLeft | Qt::AlignTop, tempStr);

	//����뾶����
	tempStr.sprintf("%.1fkm", m_dis/1000);
	painter.drawText(QRectF(m_pointRadius.x() + BIG_SECTION + 10, m_pointRadius.y(), 400, 400), Qt::AlignLeft | Qt::AlignTop, tempStr);

	//������������N
	pen.setColor(QColor(0, 0, 0, 255));
	painter.setPen(pen);
	tempPoint.setX(m_x + (1.3*m_radius + 15)*cos((90 - m_piasAngle) / 360 * 2 * M_PI));
	tempPoint.setY(m_y - (1.3*m_radius + 15)*sin((90 - m_piasAngle) / 360 * 2 * M_PI));
	tempStr = "N";
	painter.drawText(QRectF(tempPoint.x() - 20, tempPoint.y() - 20, 40, 40), Qt::AlignHCenter | Qt::AlignVCenter, tempStr);

#if 0
	//��������
	font.setPixelSize(24);
	painter.setFont(font);
	tempStr.sprintf("%d", m_cutNum);
	tempRect.setRect((m_pointAddNum.x() + m_pointMinusNum.x()) / 2 - 8, (m_pointAddNum.y() + m_pointMinusNum.y()) / 2 - 16, 400, 400);
	painter.drawText(tempRect, Qt::AlignLeft | Qt::AlignTop, tempStr);

	//����������Χ��Ȧ
	painter.setBrush(Qt::NoBrush);
	pen.setWidth(2);
	painter.setPen(pen);
	tempRect.setRect((m_pointAddNum.x() + m_pointMinusNum.x()) / 2 - 18, (m_pointAddNum.y() + m_pointMinusNum.y()) / 2 - 18, 30, 30);
	painter.drawEllipse(tempRect);

	//tempStr.sprintf("���ȣ�%.6f��\nγ�ȣ�%.6f\n���룺%.2f��", m_lng, m_lat, m_dis);
#endif

	//ָ�򱱷��ļ�ͷ
	pen.setColor(QColor(0, 0, 0, 255));
	pen.setWidth(2);
	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);

	painter.save();
	painter.translate(m_x, m_y);
	painter.rotate(m_piasAngle);

	painter.setPen(pen);
	painter.drawLine(0, 0, 0, 0 - 1.3*m_radius + 5);

	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(0, 0, 0, 255));
	painter.drawPolygon(QPolygon(m_vectorArrow2));

	painter.restore();

	//ָ���ʼ����ļ�ͷ
	pen.setColor(QColor(255, 140, 0, 255));
	pen.setWidth(4);
	pen.setStyle(Qt::DotLine);

	painter.save();
	painter.translate(m_x, m_y);

	//tempAngle = -1 * (m_startAngle - 90);
	//tempAngle = tempAngle + 90 + m_piasAngle;
	//if (tempAngle > 360)
	//	tempAngle -= 360;
	//else if (tempAngle < 0)
	//	tempAngle += 360;

	painter.rotate(m_startAngle + m_piasAngle);

	painter.setPen(pen);
	painter.drawLine(0, 0, 0, 0 - 1.3*m_radius + 5);
	
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(255, 140, 0, 255));
	painter.drawPolygon(QPolygon(m_vectorArrow2));

	painter.restore();

	//����
	painter.end();

	m_arrow1->Draw();
	m_arrow2->Draw();
}

//��ƽ��
float FanShapedSection::Square(const double num)
{
	return num*num;
}

//��������
float FanShapedSection::TwoPtDistance(const QPointF &pt1, const QPointF &pt2)
{
	return sqrt(Square(pt2.x() - pt1.x()) + Square(pt2.y() - pt1.y()));
}