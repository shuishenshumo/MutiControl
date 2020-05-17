#ifndef BASECTRL_H
#define BASECTRL_H

#include <QWidget>

class BaseCtrl : public QWidget
{
	Q_OBJECT
public:
	BaseCtrl(QWidget *parent);
	~BaseCtrl();

	virtual void Draw() = 0;
	virtual void Refresh() = 0;

protected:
	QWidget *m_parent;	//父对象，必须要

	bool m_isShow;	//是否显示

	float m_lat;	//WGS84纬度
	float m_lng;	//WGS84经度
	float m_mkLat;	//墨卡托纬度(WGS84->GCJ02->墨卡托)
	float m_mkLng;	//墨卡托经度(WGS84->GCJ02->墨卡托)
	int m_x;		//图形绘制关键点屏幕像素X坐标
	int m_y;		//图形绘制关键点屏幕像素Y坐标
	int m_x2;		//图形绘制关键点屏幕像素X坐标
	int m_y2;		//图形绘制关键点屏幕像素Y坐标
	int m_width;
	int m_height;

	int IsInCtrlSection(QRectF rect, QPointF point);

public:
	void SetShow(bool isShow);			//设置是否可见
	void SetLat(float lat);		//设置WGS84纬度
	void SetLng(float lng);		//设置WGS84经度
	void SetMkLat(float mklat); //设置墨卡托纬度
	void SetMkLng(float mklng); //设置墨卡托经度

	void SetKeyPoint(int x, int y);	//设置控件关键点
	void SetKeyPoint2(int x, int y);
	void AdjustKeyPoint(int xPias, int yPias);	//通过偏离像素设置控件关键点

	void SetX(int x);	//设置关键点坐标X值
	void SetY(int y);	//设置关键点坐标Y值
	void SetX2(int x);	//设置关键点坐标X值
	void SetY2(int y);	//设置关键点坐标Y值
	void SetWidth(int width);
	void SetHeight(int height);

	bool GetShow();		//获取是否可见
	float GetLat();		//获取设置WGS84纬度
	float GetLng();		//获取WGS84经度
	float GetMkLat();	//获取墨卡托纬度
	float GetMkLng();	//获取墨卡托经度
	int GetX();			//获取关键点坐标X值
	int GetY();			//获取关键点坐标Y值
	int GetX2();			//获取关键点坐标X值
	int GetY2();
	int GetWidth();
	int GetHeight();
};


#endif