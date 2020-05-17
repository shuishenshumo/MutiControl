#ifndef OPENGL_H
#define OPENGL_H

#include <QWidget>
#include "geometryengine.h"
#include "VertexCalc.h"
#include "timerthread.h"
#include "MapCalc.h"
#include "Point3D.h"
#include "qhld.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "line.h"
#include <QMap>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QPainter>
#include <qpushbutton.h>
#include <QTableView>
#include <QStandardItemModel>
#include <QGridLayout>
#include <qstackedwidget.h>
#include <qstring.h>
#include <qtimer.h>
#include <QPointF>
#include <QGraphicsView>
#include <QProcess>
#include <QWindow>
#include <qabstractnativeeventfilter.h>
#include "mainwindow.h"
//OpenCV
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "TCP.h"
//using namespace cv;
#pragma comment(lib, "user32.lib")
//科大讯费语音识别线程
#include "SRComThread.h"

//云知声语音识别类
#include "SpeechYZS.h"

//单声道语音合成线程
#include "TextToSpeech.h"

//
#include "HotasThread.h"

//自定义VPAS控件
#include "VAPS.h"
typedef struct
{
	vxtInt value;
}VapsMsg;

//自定义Qt控件
#include "qfanshaped.h"
#include "qtitle.h"
#include "qfirstmenu.h"
#include "qtargetposinfo.h"
#include "qstopwindow.h"

//自定义QPainter控件
#include "FanShapedSection.h"
#include "MapMarkPoint.h"
#include "MapMarkPoint2.h"
#include "SearchMenu.h"
#include "Compass.h"
#include "Location.h"
#include "LongPressFlag.h"
#include "TouchPointFlag.h"
#include "Rect.h"

//多通道输入信号处理
#include "MorphologyInput.h"

//自定义数据
#include "ShapedData.h"

class OpenGL : public QOpenGLWidget, protected QOpenGLFunctions, public QAbstractNativeEventFilter

{
	Q_OBJECT

public:
	OpenGL(QWidget *parent);
	~OpenGL();

	QWidget *m_parent;
	
protected:
	//
	bool event(QEvent *ev);
	
	//重载函数
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

	//初始化
	void initShaders();
    void initTextures();

	//自定义3D模型绘制函数
	void drawElement(VertexCalc *vertexCalc, QVector3D xyz, float angleX, float angleY);

	//绘制函数
	void drawOpenGL(GLenum mode);

public:
	//
	int m_isPainting;
	
	//OpenGL 3D模型（包含顶点位置和着色段的信息）
	VertexCalc m_map;
	VertexCalc m_sky[4];
	VertexCalc m_sphereColor;
	VertexCalc m_sphereLines;
	VertexCalc m_sphereColorGD;
	VertexCalc m_sphereLinesGD;
	VertexCalc m_curvedSurfaceColor;
	VertexCalc m_coneColor;
	VertexCalc m_sphereBand;
	VertexCalc m_target;
	VertexCalc m_line;

	//
	int m_validTextureNum;
	QList<QOpenGLTexture*> m_textureList;
	QOpenGLTexture *m_textureShangHai;
	QOpenGLTexture *m_textureShangHai2;
	QList<QOpenGLTexture*> m_textureListUp;
	QList<QOpenGLTexture*> m_textureListDown;


	//纹理处理程序
	QOpenGLShaderProgram programTexture;
	QOpenGLShaderProgram programColor;

	//绘图几何处理类
    GeometryEngine *geometries;

	//OpenGL视角控制参数

	//变换
    QMatrix4x4 m_projection;

	//记录最近时刻鼠标点击的位置
    QPointF m_lastLeftPos;
	QPointF m_lastRightPos;

	//
	int m_width;
	int m_height;

	//视角位置
	float m_fDis;
	float m_fHeight;

	//缩放相关
	int m_zoomType;
	void MapZoom(QPointF tempPoint, float para);		//缩放地图

	//旋转相关
	int m_rotateX;	//旋转中心的X坐标
	int m_rotateY;	//选择中心的Y坐标
	float m_fAxisX;		//
	float m_fAxisY;		//水平面旋转角度-最新
	float m_fAxisXOld;
	float m_fAxisYOld;	//水平面旋转角度-旧
	void MapRotate(QPointF tempPoint, float para);	//旋转地图

	//
	float m_sumX;
	float m_sumY;
	float m_paraHigh;
	int m_sumFactor;	//地图放大系数（单位：0.1个瓦片地图缩放等级）

	//偏移相关
	float m_fPiasX;
	float m_fPiasY;
	float m_fPiasRotateX;
	float m_fPiasRotateY;
	void MapDrag(QVector2D diff);					//地图平移

	//临时字符串
	QString m_sStr;

	//动态生成按钮
	QPushButton *m_pBtn;
	QPushButton *m_pBtn2;
	QPushButton *m_pBtn3;
	QPushButton *m_pBtn4;
	QPushButton *m_pBtn5;
	QPushButton *m_pBtn6;
	QPushButton *m_pBtn7;
	QPushButton *m_pBtn8;
	QPushButton *m_pBtn9;
	QPushButton *m_pBtn10;
	QPushButton *m_pBtn11;
	QPushButton *m_pBtn12;
	QPushButton *m_pBtn13;
	//使用单独的线程作为定时器
	int m_fMark;	//OpenGL画面更新次数计数
	TimerThread *m_pTimerThreadForOpenGL;	//OpenGL画面更新计时器
	TimerThread *m_pTimerForTouch;	//与时间相关的触控操作判断计时器

	//地图显示模式(0为3D模式，1为2D模式）
	int m_bOpenGLMode;

	//地图计算类
	MapCalc *m_mapCalc;

	//OpenGL坐标系原点位置
	double m_centerLat; //维度
	double m_centerLng; //经度

	//所在加载地图的左上角的墨卡托投影坐标
	double m_tlMkLat;
	double m_tlMkLng;

	//当前地图等级
	int m_curMapLevel;

	//当前地图中心位置对应的瓦片地图索引数据与像素位置
	int m_tx;
	int m_ty;
	int m_ppx;
	int m_ppy;

	//
	int m_downloadTimes;	//单次刷新周期内创建地图纹理的数量
	void LoadMapData();
	void LoadMapMethod(int level, int tx, int ty, int start, int end, float z = 0);
	int LoadOnePic(int level, int tx, int ty, bool isCreateNew,float z = 0);	//加载一张地图

	//
	void ResetCenterPos();

	//地图结算
	float GetWeightFromHeight(float height);	//在OpenGL视角高度为height的情况下，每个像素对应的OpenGL单位
	float GetHighWeightFromLevel(int level);	//

	float GetHeightFromWeight(float weight);	//根据每个像素对应的OpenGL单位，计算OpenGL视角高度height
	float GetHeightFromLevel(int level);		//

	int GetLevelFromHeight(float height);		//

	//OpenCV处理
	cv::VideoCapture g_pCapture;

	//语音识别
	bool m_isSR;
	HANDLE m_srHandle;
	SRComThread *m_recvThread;
	SpeechYZS *m_pSpeechYZS;

	//语音合成
	TextToSpeech *m_textToSpeech;
	
	//
	HotasThread *m_pHotasThread;
	int m_hotasButtonState;

	//触控相关
	//NativeEventFilterZ *m_pw;
	float m_speed;
	QPointF m_swipeDirection;
	QPointF m_swipePrePoint;
	QPointF m_swipePostPoint;
	QPointF m_oldPoint;			//用于记录旧点
	QPointF m_oldPoint2;
	QPointF m_pressPoint;		//用于记录单指按下后不做位置变化的点
	int m_touchPointNum;		//当前触控点的数量
	int m_touchLongPressTimes;	//用于判断触控长按的次数
	bool m_bIsBeginTouch;		//是否开始触控
	bool m_bIsTouchChange;		//是否进行触控的动作
	bool m_bIsTouchLeave;		//是否当前没有触控动作
	bool m_bIsSecondPointDrag;	//判断是否是由触控事件、而不是鼠标拖动事件，引起的拖动
	bool m_bIsTouchValid;		//判断触控的轻触判断是否有效
	bool m_bIsStartCalcTap;		//开始进行轻触操作判断
	void UpdateTouchState();
	void CalcSwipe(QPointF point1, QPointF point2);	//轻扫计算
	WPARAM a_WParam2=0;
	LPARAM a_LParam2=0;
	//获取系统触控消息
	virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE;
	//长按反馈
	LongPressFlag *m_pLongPressFlag;

	void SetLongPressPos(int x, int y);
	void SetLongPressPercent(float value);

	//落点反馈
	TouchPointFlag *m_pTouchPointFlag[MAX_TOUCH_NUM];
	void ClearFigurePos();
	void ShowFigurePos(QPointF point, int index);

	//词法层事件处理函数
	bool OnLButtonDown(int x, int y);
	bool OnLButtonUp(int x, int y);
	bool OnMouseMove(int x, int y);
	bool OnMouseWheel(int x, int y, short zDelta);

	//自定义数据对象
	ShapedData *m_pShapedData;
	
	//自定义控件（VAPS）（有待为不同的VAPS控件生成不同的对象）
	VAPS* m_vaps1;
	VAPS* m_vaps2;
	VAPS* m_vaps3;
	VAPS* m_vaps4;
	VapsMsg *m_vapsMsgRecv;
	VapsMsg *m_vapsMsgSend;
	VapsMsg *m_vapsMsgRecv2;
	VapsMsg *m_vapsMsgSend2;
	
	//自定义控件（QT）
	QFanShaped *m_pFanShaped;
	QTitle *m_pTitle;
	QFirstMenu *m_pFirstMenu;
	QTargetPosInfo *m_pTargetPosInfo;
	QStopWindow *m_pStopWindow;


	

	//TCP协议 语言识别模块
	TCP  tcp_connect;                       //设置两个地址，sin用来绑定
	//saClient用来从广播地址接收消息
	char tcp_cRecvBuff[800]; 
	
	int tcp_nSize, tcp_nbSize;


	//UDP协议 sd告警模块
	WSADATA threed_wsaData;      
	//指向WinSocket信息结构的指针
	WSADATA threed_wsaData2;
	SOCKET threed_sockListener;
	SOCKET threed_sockListener2;
	
	SOCKADDR_IN m_localAddr;
	SOCKADDR_IN threed_sin2, threed_saClient;                          //设置两个地址，sin用来绑定
	//saClient用来从广播地址接收消息
	char threed_cRecvBuff[20];
	char threed_cSendBuff[20];
	char threed_cSendBuff2[128];
	 //定义接收缓冲区//定义接收缓冲区
	int threed_nSize, threed_nbSize;
	int threed_iAddrLen = sizeof(threed_saClient);
	int nSize2;
	struct DL
	{
		unsigned int zt;
		unsigned int mlz;
		unsigned int cd;
		unsigned int dlbz;
		unsigned int sum;
	};
	//自定义控件（QPainter）
	FanShapedSection *m_pFanShapedSection;
	MapMarkPoint *m_pMapMarkPoint;
	MapMarkPoint *m_pMapMarkPoint2;
	MapMarkPoint *m_pMapMarkPoint3;
	MapMarkPoint *m_pMapMarkPoint4;
	MapMarkPoint *m_pMapMarkPoint5;
	MapMarkPoint *m_pMapMarkPoint6;
	MapMarkPoint *m_pMapMarkPoint7;
	MapMarkPoint *m_pMapMarkPoint8;
	MapMarkPoint *m_pMapMarkPointg[50];
	QHLD *m_pqhld;
	SearchMenu *m_pSearchMenu;
	Compass *m_pCompass;
	Location *m_pLocation;
	Rect *m_pRect;
	Line *m_pline7;
	Line *m_pline;
	Line *m_pline2;
	Line *m_pline3;
	Line *m_pline4;
	Line *m_pline5;
	Line *m_pline6;
	Line *m_plineg[50];
	//对象统一管理
	typedef enum
	{
		VPAS = 1,
		VPAS2,
		QWIDGET,
		BASECTRL
	}ENUM_OBJECT_TYPE;

	void RegisterObject(QObject *obj, ENUM_OBJECT_TYPE type);
	void DestroyObject();

	 QList<VAPS*> m_vapsList;
	 VAPS * m_vapsList2;
	
	void RegisterVAPS(VAPS *vaps);
	void DestroyVAPSList();

	QList<QWidget*> m_qtCtrlList;
	void RegisterQWidget(QWidget *widget);
	void DestroyQWidgetList();

	QList<BaseCtrl*> m_bastCtrlList;
	void RegisterBaseCtrl(BaseCtrl *ctrl);
	void DestroyBaseCtrlList();

	//上下文管理（有待思考更为复杂的上下文情况，应当包含所有显示对象当前的状态）
    ENUM_CONTEXT m_context;	//当前所处的阶段
	ENUM_CONTEXT m_oldContext;
	
	void *m_pActiveObject;		//当前正在被激活的显示组件
	void *m_pLastActiveObject;	//当前正在被激活的显示组件

	//词法原语处理
	MorphologyInput *m_pMorInput;
	
	//对不同阶段单独设计函数，提升代码可读性
	void HandleAPPEntry(Primitive *pri);
	void HandleMapFree(Primitive *pri);
	void HandleMapMark(Primitive *pri);
	void HandleMapSearch(Primitive *pri);
	void HandleMapFanShaped(Primitive *pri);
	void HandleMapAction(Primitive *pri);
	void HandleMapHLD(Primitive *pri);
	void HandleMapBJHLD(Primitive *pri);
	//根据标记点的像素位置变化，更新标记点的经纬度位置
	void RefreshMarkPoint();
	void RefreshMarkPoint2();
	void RefreshMarkPoint3();
	void RefreshMarkPoint4();
	void RefreshMarkPoint5();
	void RefreshMarkPoint6();
	void RefreshMarkPoint7();
public slots:
	void switchMapMode();
	void GDQH();
	void WQQD();
	void DHQD();
	void FCQD();
	void ZJM();
	void FTMS();
	void KDMS();
	void JJMS();
	void XTQD();
	void ZHAX();
	void HTAN();
	void recvTimerMsg();
	void recvTimerTouch();
	
	
	//触控事件
	void onTouchFirstPress(QPointF point);					//触控起始点
	void onTouchLastLeave();								//触控结束
	void onTouchTap(QPointF point);							//轻触
	void onTouchDrag(QPointF prePoint, QPointF postPoint);	//拖拽
	void onTouchRotate(QPointF point, float para);			//旋转
	void onTouchZoom(QPointF point, float para);			//缩放
	void onTouchLongPress(QPointF point, int timeMs);		//长按
	void onTouchSwipe(QPointF prePoint, QPointF postPoint);	//轻扫
	void onTouchDTap(QPointF point);						//双轻触
	//void getCP(WPARAM a_WParam, LPARAM a_LParam);//手动管理
	//鼠标事件  
	void onMousePress(QPointF point);

	void onMouseRelease(QPointF point);
	void onMouseDblClick(QPointF point);
	void onMouseMove(QPointF prePoint, QPointF postPoint);

	//滚轮事件
	void onMouseWheel(QPointF point, float para);




	//语音控制事件
	void onStartSR();
	void onStopSR();
	void HandleSRResult(QString);
	
	int GetNumFromSRResult(QString);

	//按键事件
	//void onKeyEvent(QEvent* ev);

	//接收多通道控制的结果，并执行相应动作
	//void onMultiChannelCtrl();

	//重置地图旋转角度
	void onResetAlpha();

	//重置地图中心位置到本机位置
	void onResetLocation();

	//接收一级功能菜单显示组件的消息
	void onSetMode(int mode);		//得到工作模式

	//接收搜索菜单显示组件的消息
	void onSetSearchType(int type);

	//接收标记点显示组件的消息
	void onMapMarkPointDrag(QPointF, QPointF);
	void onMapMarkPointDrag2(QPointF, QPointF);
	//接收扇形搜索数据对象的消息
	void onShapedDataChangeLat(float lat);
	void onShapedDataChangeLng(float lng);
	void onShapedDataChangeMKLat(float mkLat);
	void onShapedDataChangeMKLng(float mkLng);
	void onShapedDataChangeStartAngle(float startAngle);
	void onShapedDataChangeSpanAngle(float spanAngle);
	void onShapedDataChangeDis(float dis);
	void onShapedDataChangeDirection(int direction);

	//接收扇形搜索图形的消息
	void onShapedSectionAdjustStartAngle(float startAngle);
	void onShapedSectionAdjustSpanAngle(float spanAngle);
	void onShapedSectionAdjustRadius(float pxDis);
	void onShapedSectionReversalDirection();

	//接收扇形参数设置框的消息
	void onQFanShapedSetLat(float lat);
	void onQFanShapedSetLng(float lng);
	void onQFanShapedSetStartAngle(float startAngle);
	void onQFanShapedSetSpanAngle(float spanAngle);
	void onQFanShapedSetDis(float dis);
	void onQFanShapedSetDirection(int direction);
	void onQFanShapedCancelSearch(int type);
	void onQFanShapedActSearch(int type);

	void onQHLDSetLat(float lat);
	void onQHLDSetLng(float lng);
	void onQHLDSetLat2(float lat);
	void onQHLDSetLng2(float lng);
	void onQHLDSetLat3(float lat);
	void onQHLDSetLng3(float lng);
	void onQHLDSetLat4(float lat);
	void onQHLDSetLng4(float lng);
	void onQHLDSetLat5(float lat);
	void onQHLDSetLng5(float lng);
	void onQHLDSetLat6(float lat);
	void onQHLDSetLng6(float lng);
	void onQHLDSetLat7(float lat);
	void onQHLDSetLng7(float lng);
	void onjian1();
	void onjian2();
	void onjian3();
	void onjian4();
	void onjian5();
	void onjian6();
	void onjian7();
	//接收停止搜索窗体的消息
	void onEditSearch();
	void onStopSearch();

	//词法原语处理
	void onHandlePrimitive(Primitive* pri);

	//
	void onGetJoyData(JOYINFOEX*);
	void onGetJoyState(int);
	
	
private:
	float square(const double num);
	float TwoPtDistance(const QPointF &pt1, const QPointF &pt2);
};

#endif // OPENGL_H

