#ifndef FANSHAPEDSECTION_H
#define FANSHAPEDSECTION_H

#include "BaseCtrl.h"
#include <QWidget>
#include "Arrow.h"

#define BIG_SECTION (40)				//�ؼ�����Բ������İ뾶
#define CONCENTRIC_CIRCLE_PIAS (320)	//ͬ��Բ����ֹ���Ƶ㣩�뾶������

#define DRAG_CIRCLE_RADIUS (10)			//������קԲ������İ뾶
#define DRAG_CIRCLE_RADIUS_M (1000)		//������קԲ������İ뾶

#define TOUCH_COMPENSATE (0)			//�������򲹳�
#define ANGLE_PIAS (20)					//�ؼ����Ƶ����뾶

typedef enum
{
	FAN_AZIMUTH = 1,
	FAN_ANGLE,
	FAN_RADIUS,
	FAN_ADD,
	FAN_MINUS,
	FAN_DIRECTION,
	FAN_DRAG
}ENUM_TYPE;

class FanShapedSection : public BaseCtrl
{
	Q_OBJECT
public:
	FanShapedSection(QWidget *parent);
	~FanShapedSection();
	
	void Draw();
	void Refresh();

	int m_showType;	//1���༭״̬��2������״̬
	void SetShowType(int type);

	int m_cutNum;		//��������
	float m_startAngle;	//��ʼ����ǣ����ĸ�����Ϊ������˳��ʱ���ĸ�Ϊ������
	float m_spanAngle;	//�����
	int m_direction;	//-1��˳ʱ�룬1����ʱ��

	float m_radius;		//����뾶���ؾ��룬��λpixel
	float m_dis;		//����뾶������룬��λ��
	bool m_bIsRadiusChanged;
	
	float m_piasAngle;	//��ͼƫ�����������ͼ��ת����Ӧ�����������Ƿ�ҲӦ����ת����

	//���ò���
	void SetDis(float dis);
	void SetStartAngle(float angle);	//������ʼ�Ƕ�
	void SetSpanAngle(float angle);		//�������������
	void SetRadius(float radius);		//���������뾶
	void SetDirection(int direction);	//������������
	void SetCutNum(int num);			//�����з�����
	void SetPiasAngle(float angle);		//���õ�ͼƫ�ƽǶ�

	float GetDis();
	float GetRadius();
	float GetPiasAngle();

	void AdjustStartAngle(float anglePias);	//������ʼ�Ƕ�ƫ����
	void AdjustSpanAngle(float anglePias);	//�������������ƫ����
	void AdjustRadius(float radiusPias);	//���������뾶����ƫ����
	void AdjustDis(float disPias);			//���������뾶����ƫ����
	void ReversalDirection();				//��ת��������

	bool IsRefreshDis();
	void HasRefreshedDis();

	//���Ƽ�������
	int m_selectedIndex;
	QPointF m_point;
	
	//���η�Χ
	QVector<QPoint> m_vector;
	QVector<QPoint> m_vectorArrow1;
	QVector<QPoint> m_vectorArrow2;
	Arrow *m_arrow1;
	Arrow *m_arrow2;

	//�ؼ���λ��
	QPointF m_pointAzimuth;		//����
	QPointF m_pointAngle;		//�����
	QPointF m_pointRadius;		//�뾶
	QPointF m_pointAddNum;		//������������
	QPointF m_pointMinusNum;	//������������
	QPointF m_pointDirection;	//ת��
	QPointF m_pointDrag;		//��ק��ƽ������

	//��ʾ����
	QRectF m_showSectionAzimuth;	//����
	QRectF m_showSectionAngle;		//�����
	QRectF m_showSectionRadius;		//�뾶
	QRectF m_showSectionAddNum;		//������������
	QRectF m_showSectionMinusNum;	//������������
	QRectF m_showSectionDirection;	//˳����ʱ��
	QRectF m_showSectionDrag;		//��ק��ƽ������

	QRectF m_showPara;	//��ʾ����
	
	//��������
	QRectF m_ctrlSectionAzimuth;	//����
	QRectF m_ctrlSectionAngle;		//�����
	QRectF m_ctrlSectionRadius;		//�뾶
	QRectF m_ctrlSectionAddNum;		//������������
	QRectF m_ctrlSectionMinusNum;	//������������
	QRectF m_ctrlSectionDirection;	//˳����ʱ��
	QRectF m_ctrlSectionDrag;		//��ק��ƽ������

	//
	int IsInFanShapedSection(QPointF point);			//��point�Ƿ�������������	

	//�������Ըı�ӿ�
	int OnAddNum();
	int OnMinusNum();
	int OnZoom(QPointF point, float delta);
	int OnRotate(QPointF point, float alpha);
	int OnPress(QPointF point);
	int OnRelease(QPointF point);
	int OnMove(QPointF oldPoint, QPointF newPoint);		//���ض���

signals:
	void sigDrag(QPointF, QPointF);
	void sigAdjustStartAngle(float);
	void sigAdjustSpanAngle(float);
	void sigAdjustRadius(float);
	void sigReversalDirection();

private:
	//
	float Square(const double num);									//��ƽ��
	float TwoPtDistance(const QPointF &pt1, const QPointF &pt2);	//��������

	//
	QImage *m_pImageHeading;
	QImage *m_pImageAngle;
	QImage *m_pImageRadius;
	QImage *m_pImageDirection1;
	QImage *m_pImageDirection2;
	QImage *m_pImageAdd;
	QImage *m_pImageMinus;
};


#endif