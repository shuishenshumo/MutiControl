#include "BaseCtrl.h"
#include <qpainter.h>
#include <qdebug.h>

BaseCtrl::BaseCtrl(QWidget *parent)
{
	m_parent = parent;

	m_isShow = false;	//Ĭ�ϻ��治��ʾ

	m_lat = 0;		//WGS84γ��
	m_lng = 0;		//WGS84����

	m_mkLat = 0;	//ī����γ��(WGS84->GCJ02->ī����)
	m_mkLng = 0;	//ī���о���(WGS84->GCJ02->ī����)

	m_x = 0;		//ͼ�λ��ƹؼ�����Ļ����X����
	m_y = 0;		//ͼ�λ��ƹؼ�����Ļ����Y����
	m_x2 = 0;		//ͼ�λ��ƹؼ�����Ļ����X����
	m_y2 = 0;		//ͼ�λ��ƹؼ�����Ļ����Y����
}

BaseCtrl::~BaseCtrl()
{

}

void BaseCtrl::SetShow(bool isShow)
{
	m_isShow = isShow;
}

void BaseCtrl::SetLat(float lat)
{
	m_lat = lat;
}

void BaseCtrl::SetLng(float lng)
{
	m_lng = lng;
}

void BaseCtrl::SetMkLat(float lat)
{
	m_mkLat = lat;
}

void BaseCtrl::SetMkLng(float lng)
{
	m_mkLng = lng;
}

void BaseCtrl::SetKeyPoint(int x, int y)
{
	m_x = x;
	m_y = y;
}
void BaseCtrl::SetKeyPoint2(int x, int y)
{
	m_x2 = x;
	m_y2 = y;
}
void BaseCtrl::AdjustKeyPoint(int xPias, int yPias)
{
	m_x = m_x + xPias;
	m_y = m_y + yPias;

}

void BaseCtrl::SetX(int x)
{
	m_x = x;
}

void BaseCtrl::SetY(int y)
{
	m_y = y;
}
void BaseCtrl::SetX2(int x)
{
	m_x2 = x;
}

void BaseCtrl::SetY2(int y)
{
	m_y2 = y;
}

void BaseCtrl::SetWidth(int width)
{
	m_width = width;
}

void BaseCtrl::SetHeight(int height)
{
	m_height = height;
}

bool BaseCtrl::GetShow()
{
	return m_isShow;
}

float BaseCtrl::GetLat()
{
	return m_lat;
}

float BaseCtrl::GetLng()
{
	return m_lng;
}

float BaseCtrl::GetMkLat()
{
	return m_mkLat;
}

float BaseCtrl::GetMkLng()
{
	return m_mkLng;
}

int BaseCtrl::GetX()
{
	return m_x;
}

int BaseCtrl::GetY()
{
	return m_y;
}
int BaseCtrl::GetX2()
{
	return m_x2;
}

int BaseCtrl::GetY2()
{
	return m_y2;
}

int BaseCtrl::GetWidth()
{
	return m_width;
}

int BaseCtrl::GetHeight()
{
	return m_height;
}

int BaseCtrl::IsInCtrlSection(QRectF rect, QPointF point)
{
	if (point.x() > rect.left() && point.x() < rect.right() && point.y() > rect.top() && point.y() < rect.bottom())
		return 1;
	else
		return 0;
}