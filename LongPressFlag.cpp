#include "LongPressFlag.h"
#include <qpainter.h>
#include <qmath.h>
#include <qdebug.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

LongPressFlag::LongPressFlag(QWidget *parent)
	: BaseCtrl(parent)
{
	m_radius = 0;
}

LongPressFlag::~LongPressFlag()
{

}

//绘制
void LongPressFlag::Draw()
{
	QPen pen;
	QPainter painter;
	float percent = m_percent;
	float startAngle = 0, spanAngle = 0;

	if (m_percent > 1e-6)
	{
		startAngle = 90 * 16;
		spanAngle = -1.0 * percent * 360 * 16;

		//开始
		painter.begin(m_parent);
		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

		pen.setColor(QColor(207, 218, 255, 255));
		pen.setWidth(5);
		painter.setPen(pen);

		painter.drawArc(m_showSection, startAngle, spanAngle);

		//结束
		painter.end();
	}
}

void LongPressFlag::SetKeyPoint(int x, int y)
{
	m_x = x;
	m_y = y;
}

void LongPressFlag::SetRadius(int x)
{
	m_radius = x;
}

void LongPressFlag::SetPercent(float percent)
{
	m_percent = percent;
}

void LongPressFlag::Refresh()
{
	m_showSection.setRect(m_x - m_radius, m_y - m_radius, 2 * m_radius , 2 * m_radius);
}