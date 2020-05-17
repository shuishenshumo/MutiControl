#include "line.h"
#include "Config.h"
#include <QPainter>
#include <QMovie>
#include <QBitmap>
#include <QtWidgets/QMainWindow>
#include <QVector3D>
#include <windows.h>
#include <qstring.h>
#include <QTextCodec>
#include <QLayOut>
#include <QProcess>
#include <QLabel>
#include "opengl.h"


#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif
Line::Line(QWidget *parent)
	:BaseCtrl(parent)
{
	
	
}

Line::~Line()
{

}

int a;
int b;
int c;
int d;
int a2;
int b2;
int c2;
int d2;
int a3;
int b3;
int c3;
int d3;
int a4;
int b4;
int c4;
int d4;
int a5;
int b5;
int c5;
int d5;
int a6;
int b6;
int c6;
int d6;
void Line::getline(int x, int y, int xx, int yy)
{
	a = x;
	b = y;
	c = xx;
	d = yy;

}
void Line::getline2(int x, int y, int xx, int yy)
{
	a2 = x;
	b2 = y;
	c2 = xx;
	d2 = yy;

}
void Line::getline3(int x, int y, int xx, int yy)
{
	a3 = x;
	b3 = y;
	c3 = xx;
	d3 = yy;

}
void Line::getline4(int x, int y, int xx, int yy)
{
	a4 = x;
	b4 = y;
	c4 = xx;
	d4 = yy;

}
void Line::getline5(int x, int y, int xx, int yy)
{
	a5 = x;
	b5 = y;
	c5 = xx;
	d5 = yy;

}
void Line::getline6(int x, int y, int xx, int yy)
{
	a6 = x;
	b6 = y;
	c6 = xx;
	d6 = yy;

}

void Line::FrameInit()
{
	QTimer *timer;
	timer = new QTimer(this);
	
}
void Line::Draw()
{
	if (m_isShow == false)
		return;
	QPainter painter;
	painter.begin(m_parent);
	QPen pen = painter.pen();
	pen.setWidth(7);
	pen.setColor(QColor(252, 138, 0, 153));
	painter.setPen(pen);
	painter.drawLine(a, b, c, d);
	QString str ;
	pen.setColor(QColor(Qt::black));
	QFont font = painter.font();
	font.setBold(true);
	font.setPixelSize(50);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(a-12, b+16,tr("1"));
	painter.drawText(c-12, d+16,tr("2"));
	painter.end();
}
void Line::Draw2()
{
	if (m_isShow == false)
		return;
	QPainter painter;
	painter.begin(m_parent);
	QPen pen = painter.pen();
	pen.setWidth(7);
	pen.setColor(QColor(252, 138, 0, 153));
	painter.setPen(pen);
	painter.drawLine(a2, b2, c2, d2);
	QString str;
	pen.setColor(QColor(Qt::black));
	QFont font = painter.font();
	font.setBold(true);
	font.setPixelSize(50);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(c2 - 12, d2 + 16, tr("3"));
	painter.end();
}
void Line::Draw3()
{
	if (m_isShow == false)
		return;
	QPainter painter;
	painter.begin(m_parent);
	QPen pen = painter.pen();

	pen.setWidth(7);
	pen.setColor(QColor(252, 138, 0, 153));
	painter.setPen(pen);
	painter.drawLine(a3, b3, c3, d3);
	QString str;
	pen.setColor(QColor(Qt::black));
	QFont font = painter.font();
	font.setBold(true);
	font.setPixelSize(50);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(c3 - 12, d3 + 16, tr("4"));
	painter.end();
}
void Line::Draw4()
{
	if (m_isShow == false)
		return;
	QPainter painter;
	painter.begin(m_parent);
	QPen pen = painter.pen();
	pen.setWidth(7);
	pen.setColor(QColor(252, 138, 0, 153));
	painter.setPen(pen);
	painter.drawLine(a4, b4, c4, d4);
	QString str;
	pen.setColor(QColor(Qt::black));
	QFont font = painter.font();
	font.setBold(true);
	font.setPixelSize(50);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(c4 - 12, d4 + 16, tr("5"));
	painter.end();
}
void Line::Draw5()
{
	if (m_isShow == false)
		return;
	QPainter painter;
	painter.begin(m_parent);
	QPen pen = painter.pen();
	pen.setWidth(7);
	pen.setColor(QColor(252, 138, 0, 153));
	painter.setPen(pen);
	painter.drawLine(a5, b5, c5, d5);
	QString str;
	pen.setColor(QColor(Qt::black));
	QFont font = painter.font();
	font.setBold(true);
	font.setPixelSize(50);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(c5 - 12, d5 + 16, tr("6"));
	painter.end();
}
void Line::Draw6()
{
	if (m_isShow == false)
		return;
	QPainter painter;
	painter.begin(m_parent);
	QPen pen = painter.pen();
	pen.setWidth(7);
	pen.setColor(QColor(252, 138, 0, 153));
	painter.setPen(pen);
	painter.drawLine(a6, b6, c6, d6);
	QString str;
	pen.setColor(QColor(Qt::black));
	QFont font = painter.font();
	font.setBold(true);
	font.setPixelSize(50);
	painter.setPen(pen);
	painter.setFont(font);
	painter.drawText(c6 - 12, d6 + 16, tr("7"));
	painter.end();
}

void Line::Refresh()
{

}