#include "Compass.h"
#include <qpainter.h>
#include <qmath.h>
#include <qdebug.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

Compass::Compass(QWidget *parent)
	: BaseCtrl(parent)
{
	m_alpha = 90;

	m_state = 0;

	m_pImage = new QImage(QCOMPASS_DEFAULT_IMAGE_PATH);
	m_pImageInter = new QImage("Resource/icon-N.png");
	m_pImagePressed = new QImage(QCOMPASS_PRESSED_IMAGE_PATH);
}

Compass::~Compass()
{
	if (m_pImage != NULL)
	{
		delete m_pImage;
	}

	if (m_pImageInter != NULL)
	{
		delete m_pImageInter;
	}

	if (m_pImagePressed != NULL)
	{
		delete m_pImagePressed;
	}
}

//绘制
void Compass::Draw()
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

		//painter.setBrush(QColor(255, 255, 255, 50));
		//painter.drawEllipse(m_showSection);

		painter.save();
		painter.translate(m_x, m_y);
		painter.rotate(m_alpha);
		if (m_state == 0)
			painter.drawImage(m_showSection, *m_pImage);
		else
			painter.drawImage(m_showSection, *m_pImagePressed);
		//painter.rotate(-m_alpha);
		//painter.drawImage(m_showSectionInter, *m_pImageInter);
		painter.restore();

		//结束
		painter.end();
	}
}

void Compass::Refresh()
{
	m_showSection.setRect(0 - COMPASS_RADIUS, 0 - COMPASS_RADIUS, 2 * COMPASS_RADIUS, 2 * COMPASS_RADIUS);
	m_showSectionInter.setRect(0 - 10, 0 - 10, 2 * 10, 2 * 10);
}

int Compass::IsInSection(QPointF point)
{
	int x = abs(point.x() - m_x);
	int y = abs(point.y() - m_y);
	if (x <= COMPASS_RADIUS && y <= COMPASS_RADIUS)
	{
		return 1;
	}
	return 0;
}

void Compass::SetAlpha(float alpha)
{
	m_alpha = alpha;
}

int Compass::OnPress(QPointF point)
{
	if (IsInSection(point))
	{
		m_state = 1;
		return 1;
	}
	return 0;
}

int Compass::OnRelease(QPointF point)
{
	if (m_state == 1)
	{
		emit sigResetAlpha();
		m_state = 0;
	}
	return 0;
}

int Compass::OnMove(QPointF pointOld, QPointF pointNew)
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