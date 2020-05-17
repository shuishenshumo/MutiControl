#ifndef SHAPEDDATA_H
#define SHAPEDDATA_H

#include <QWidget>


class ShapedData : public QWidget
{
	Q_OBJECT
public:
	ShapedData(QWidget *parent = 0);
	~ShapedData();

	float m_lat;	//WGS84γ��
	float m_lng;	//WGS84����
	float m_mkLat;	//ī����γ��(WGS84->GCJ02->ī����)
	float m_mkLng;	//ī���о���(WGS84->GCJ02->ī����)

	float m_startAngle;	//��ʼ����ǣ��ݶ�������Ϊ��λ��˳ʱ��Ϊ����
	float m_spanAngle;	//�����
	float m_dis;		//����뾶������룬��λ��
	int m_direction;	//-1��˳ʱ�룬1����ʱ��

	void SetLat(float lat);		//����WGS84γ��
	void SetLng(float lng);		//����WGS84����
	void SetMkLat(float mklat); //����ī����γ��
	void SetMkLng(float mklng); //����ī���о���

	float GetLat();		//��ȡ����WGS84γ��
	float GetLng();		//��ȡWGS84����
	float GetMkLat();	//��ȡī����γ��
	float GetMkLng();	//��ȡī���о���

	void SetStartAngle(float angle);	//������ʼ�Ƕ�
	void SetSpanAngle(float angle);		//�������������
	void SetDis(float dis);				//���������뾶����λ�ף�
	void SetDirection(int direction);	//������������

	float GetStartAngle();				//��ȡ��ʼ�Ƕ�
	float GetSpanAngle();				//��ȡ���������
	float GetDis();						//��ȡ�����뾶����λ�ף�
	int GetDirection();					//��ȡ��������

	void AdjustStartAngle(float anglePias);	//������ʼ�Ƕ�ƫ����
	void AdjustSpanAngle(float anglePias);	//�������������ƫ����
	void AdjustDis(float disPias);			//���������뾶����ƫ����
	void ReversalDirection();				//��ת��������

signals:
	void sigChangeLat(float);
	void sigChangeLng(float);
	void sigChangeMKLat(float);
	void sigChangeMKLng(float);
	void sigChangeStartAngle(float);
	void sigChangeSpanAngle(float);
	void sigChangeDis(float);
	void sigChangeDirection(int);

private:
	QWidget *m_pParent;
};

#endif