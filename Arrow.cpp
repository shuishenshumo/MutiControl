#include "Arrow.h"
#include "Config.h"
#include <QPainter>

Arrow::Arrow(QWidget *parent)
	:BaseCtrl(parent)
{
	m_alpha = 0;
	m_length = 120;
	m_startPos = 50;
}

Arrow::~Arrow()
{

}

void Arrow::Draw()
{
	if (m_isShow == false)
		return;

	QPen pen;
	QFont font;
	QBrush brush;
	QPainter painter;

	painter.begin(m_parent);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

	painter.save();
	painter.translate(m_x, m_y);
	painter.rotate(m_alpha);

	pen.setColor(QColor(255, 120, 0, 255));
	pen.setWidth(4);
	pen.setStyle(Qt::SolidLine);
	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	painter.setPen(pen);
	
	painter.drawLine(QPointF(0, -m_startPos), QPointF(0, -m_length));

	painter.setBrush(QColor(255, 120, 0, 255));

	m_vectorArrow.clear();
	m_vectorArrow.append(QPoint(0, -m_length));
	m_vectorArrow.append(QPoint(0 - 10, -m_length + 20));
	m_vectorArrow.append(QPoint(0 + 10, -m_length + 20));
	m_vectorArrow.append(QPoint(0, -m_length));
	painter.drawPolygon(QPolygon(m_vectorArrow));

	painter.restore();

	painter.end();
}

void Arrow::Refresh()
{
	
}

void Arrow::SetAlpha(float alpha)
{
	m_alpha = alpha;
}

void Arrow::SetLength(float length)
{
	m_length = length;
}

void Arrow::SetStartPos(float pos)
{
	m_startPos = pos;
}