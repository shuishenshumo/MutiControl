#ifndef SHAPEDDATA_H
#define SHAPEDDATA_H

#include <QWidget>


class ShapedData : public QWidget
{
	Q_OBJECT
public:
	ShapedData(QWidget *parent = 0);
	~ShapedData();

	float m_lat;	//WGS84纬度
	float m_lng;	//WGS84经度
	float m_mkLat;	//墨卡托纬度(WGS84->GCJ02->墨卡托)
	float m_mkLng;	//墨卡托经度(WGS84->GCJ02->墨卡托)

	float m_startAngle;	//初始航向角（暂定以正北为零位、顺时针为正）
	float m_spanAngle;	//扇面角
	float m_dis;		//扇面半径物理距离，单位米
	int m_direction;	//-1：顺时针，1：逆时针

	void SetLat(float lat);		//设置WGS84纬度
	void SetLng(float lng);		//设置WGS84经度
	void SetMkLat(float mklat); //设置墨卡托纬度
	void SetMkLng(float mklng); //设置墨卡托经度

	float GetLat();		//获取设置WGS84纬度
	float GetLng();		//获取WGS84经度
	float GetMkLat();	//获取墨卡托纬度
	float GetMkLng();	//获取墨卡托经度

	void SetStartAngle(float angle);	//设置起始角度
	void SetSpanAngle(float angle);		//设置搜索扇面角
	void SetDis(float dis);				//设置搜索半径（单位米）
	void SetDirection(int direction);	//设置搜索方向

	float GetStartAngle();				//获取起始角度
	float GetSpanAngle();				//获取搜索扇面角
	float GetDis();						//获取搜索半径（单位米）
	int GetDirection();					//获取搜索方向

	void AdjustStartAngle(float anglePias);	//设置起始角度偏移量
	void AdjustSpanAngle(float anglePias);	//设置搜索扇面角偏移量
	void AdjustDis(float disPias);			//设置搜索半径缩放偏移量
	void ReversalDirection();				//翻转搜索方向

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