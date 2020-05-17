#ifndef FANSHAPEDSECTION_H
#define FANSHAPEDSECTION_H

#include "BaseCtrl.h"
#include <QWidget>
#include "Arrow.h"

#define BIG_SECTION (40)				//关键控制圆形区域的半径
#define CONCENTRIC_CIRCLE_PIAS (320)	//同心圆（防止控制点）半径增加量

#define DRAG_CIRCLE_RADIUS (10)			//中心拖拽圆形区域的半径
#define DRAG_CIRCLE_RADIUS_M (1000)		//中心拖拽圆形区域的半径

#define TOUCH_COMPENSATE (0)			//触控区域补偿
#define ANGLE_PIAS (20)					//关键控制点间隔半径

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

	int m_showType;	//1：编辑状态；2：引导状态
	void SetShowType(int type);

	int m_cutNum;		//扇面数量
	float m_startAngle;	//初始航向角（以哪个方向为正方向？顺逆时针哪个为正？）
	float m_spanAngle;	//扇面角
	int m_direction;	//-1：顺时针，1：逆时针

	float m_radius;		//扇面半径像素距离，单位pixel
	float m_dis;		//扇面半径物理距离，单位米
	bool m_bIsRadiusChanged;
	
	float m_piasAngle;	//地图偏移量（如果地图旋转，对应的搜索扇面是否也应当旋转？）

	//设置参数
	void SetDis(float dis);
	void SetStartAngle(float angle);	//设置起始角度
	void SetSpanAngle(float angle);		//设置搜索扇面角
	void SetRadius(float radius);		//设置搜索半径
	void SetDirection(int direction);	//设置搜索方向
	void SetCutNum(int num);			//设置切分数量
	void SetPiasAngle(float angle);		//设置地图偏移角度

	float GetDis();
	float GetRadius();
	float GetPiasAngle();

	void AdjustStartAngle(float anglePias);	//设置起始角度偏移量
	void AdjustSpanAngle(float anglePias);	//设置搜索扇面角偏移量
	void AdjustRadius(float radiusPias);	//设置搜索半径缩放偏移量
	void AdjustDis(float disPias);			//设置搜索半径缩放偏移量
	void ReversalDirection();				//翻转搜索方向

	bool IsRefreshDis();
	void HasRefreshedDis();

	//控制激活区域
	int m_selectedIndex;
	QPointF m_point;
	
	//扇形范围
	QVector<QPoint> m_vector;
	QVector<QPoint> m_vectorArrow1;
	QVector<QPoint> m_vectorArrow2;
	Arrow *m_arrow1;
	Arrow *m_arrow2;

	//关键点位置
	QPointF m_pointAzimuth;		//航向
	QPointF m_pointAngle;		//扇面角
	QPointF m_pointRadius;		//半径
	QPointF m_pointAddNum;		//增加扇面数量
	QPointF m_pointMinusNum;	//减少扇面数量
	QPointF m_pointDirection;	//转向
	QPointF m_pointDrag;		//拖拽、平移区域

	//显示区域
	QRectF m_showSectionAzimuth;	//航向
	QRectF m_showSectionAngle;		//扇面角
	QRectF m_showSectionRadius;		//半径
	QRectF m_showSectionAddNum;		//增加扇面数量
	QRectF m_showSectionMinusNum;	//增加扇面数量
	QRectF m_showSectionDirection;	//顺、逆时针
	QRectF m_showSectionDrag;		//拖拽、平移区域

	QRectF m_showPara;	//显示参数
	
	//控制区域
	QRectF m_ctrlSectionAzimuth;	//航向
	QRectF m_ctrlSectionAngle;		//扇面角
	QRectF m_ctrlSectionRadius;		//半径
	QRectF m_ctrlSectionAddNum;		//增加扇面数量
	QRectF m_ctrlSectionMinusNum;	//增加扇面数量
	QRectF m_ctrlSectionDirection;	//顺、逆时针
	QRectF m_ctrlSectionDrag;		//拖拽、平移区域

	//
	int IsInFanShapedSection(QPointF point);			//点point是否在扇面区域里	

	//扇面属性改变接口
	int OnAddNum();
	int OnMinusNum();
	int OnZoom(QPointF point, float delta);
	int OnRotate(QPointF point, float alpha);
	int OnPress(QPointF point);
	int OnRelease(QPointF point);
	int OnMove(QPointF oldPoint, QPointF newPoint);		//触控动作

signals:
	void sigDrag(QPointF, QPointF);
	void sigAdjustStartAngle(float);
	void sigAdjustSpanAngle(float);
	void sigAdjustRadius(float);
	void sigReversalDirection();

private:
	//
	float Square(const double num);									//求平方
	float TwoPtDistance(const QPointF &pt1, const QPointF &pt2);	//两点间距离

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