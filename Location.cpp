#include "Location.h"
#include <qpainter.h>
#include <qmath.h>
#include <qdebug.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

Location::Location(QWidget *parent)
	: BaseCtrl(parent)
{
	m_state = 0;

	m_pImage = new QImage(LOCATION_DEFAULT_IMAGE_PATH);
	m_pImagePressed = new QImage(LOCATION_PRESSED_IMAGE_PATH);
}

Location::~Location()
{
	if (m_pImage != NULL)
	{
		delete m_pImage;
	}

	if (m_pImagePressed != NULL)
	{
		delete m_pImagePressed;
	}
}

//绘制
void Location::Draw()
{
	QPen pen;
	QBrush brush;
	QPainter painter;

	if (m_isShow == true)
	{
		//开始
		painter.begin(m_parent);
		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

		pen.setColor(Qt::white);
		pen.setWidth(1);
		painter.setPen(pen);

		painter.save();
		painter.translate(m_x, m_y);
		if (m_state == 0)
			painter.drawImage(m_showSection, *m_pImage);
		else
			painter.drawImage(m_showSection, *m_pImagePressed);
		painter.restore();

		//结束
		painter.end();
	}
}

void Location::Refresh()
{
	m_showSection.setRect(0 - LOCATION_RADIUS, 0 - LOCATION_RADIUS, 2 * LOCATION_RADIUS, 2 * LOCATION_RADIUS);
}

int Location::IsInSection(QPointF point)
{
	int x = abs(point.x() - m_x);
	int y = abs(point.y() - m_y);
	if (x <= LOCATION_RADIUS && y <= LOCATION_RADIUS)
	{
		return 1;
	}
	return 0;
}

int Location::OnPress(QPointF point)
{
	if (IsInSection(point))
	{
		m_state = 1;
		return 1;
	}
	return 0;
}

int Location::OnRelease(QPointF point)
{
	if (m_state == 1)
	{
		emit sigResetLocation();
		m_state = 0;
	}
	return 0;
}

int Location::OnMove(QPointF pointOld, QPointF pointNew)
{
	if (m_state == 1)
	{
		if (IsInSection(pointNew))
		{
			m_state = 0;
		}
	}
	return 0;
}