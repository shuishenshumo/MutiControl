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
	QWidget *m_parent;	//�����󣬱���Ҫ

	bool m_isShow;	//�Ƿ���ʾ

	float m_lat;	//WGS84γ��
	float m_lng;	//WGS84����
	float m_mkLat;	//ī����γ��(WGS84->GCJ02->ī����)
	float m_mkLng;	//ī���о���(WGS84->GCJ02->ī����)
	int m_x;		//ͼ�λ��ƹؼ�����Ļ����X����
	int m_y;		//ͼ�λ��ƹؼ�����Ļ����Y����
	int m_x2;		//ͼ�λ��ƹؼ�����Ļ����X����
	int m_y2;		//ͼ�λ��ƹؼ�����Ļ����Y����
	int m_width;
	int m_height;

	int IsInCtrlSection(QRectF rect, QPointF point);

public:
	void SetShow(bool isShow);			//�����Ƿ�ɼ�
	void SetLat(float lat);		//����WGS84γ��
	void SetLng(float lng);		//����WGS84����
	void SetMkLat(float mklat); //����ī����γ��
	void SetMkLng(float mklng); //����ī���о���

	void SetKeyPoint(int x, int y);	//���ÿؼ��ؼ���
	void SetKeyPoint2(int x, int y);
	void AdjustKeyPoint(int xPias, int yPias);	//ͨ��ƫ���������ÿؼ��ؼ���

	void SetX(int x);	//���ùؼ�������Xֵ
	void SetY(int y);	//���ùؼ�������Yֵ
	void SetX2(int x);	//���ùؼ�������Xֵ
	void SetY2(int y);	//���ùؼ�������Yֵ
	void SetWidth(int width);
	void SetHeight(int height);

	bool GetShow();		//��ȡ�Ƿ�ɼ�
	float GetLat();		//��ȡ����WGS84γ��
	float GetLng();		//��ȡWGS84����
	float GetMkLat();	//��ȡī����γ��
	float GetMkLng();	//��ȡī���о���
	int GetX();			//��ȡ�ؼ�������Xֵ
	int GetY();			//��ȡ�ؼ�������Yֵ
	int GetX2();			//��ȡ�ؼ�������Xֵ
	int GetY2();
	int GetWidth();
	int GetHeight();
};


#endif