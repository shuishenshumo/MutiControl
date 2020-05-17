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
//�ƴ�Ѷ������ʶ���߳�
#include "SRComThread.h"

//��֪������ʶ����
#include "SpeechYZS.h"

//�����������ϳ��߳�
#include "TextToSpeech.h"

//
#include "HotasThread.h"

//�Զ���VPAS�ؼ�
#include "VAPS.h"
typedef struct
{
	vxtInt value;
}VapsMsg;

//�Զ���Qt�ؼ�
#include "qfanshaped.h"
#include "qtitle.h"
#include "qfirstmenu.h"
#include "qtargetposinfo.h"
#include "qstopwindow.h"

//�Զ���QPainter�ؼ�
#include "FanShapedSection.h"
#include "MapMarkPoint.h"
#include "MapMarkPoint2.h"
#include "SearchMenu.h"
#include "Compass.h"
#include "Location.h"
#include "LongPressFlag.h"
#include "TouchPointFlag.h"
#include "Rect.h"

//��ͨ�������źŴ���
#include "MorphologyInput.h"

//�Զ�������
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
	
	//���غ���
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

	//��ʼ��
	void initShaders();
    void initTextures();

	//�Զ���3Dģ�ͻ��ƺ���
	void drawElement(VertexCalc *vertexCalc, QVector3D xyz, float angleX, float angleY);

	//���ƺ���
	void drawOpenGL(GLenum mode);

public:
	//
	int m_isPainting;
	
	//OpenGL 3Dģ�ͣ���������λ�ú���ɫ�ε���Ϣ��
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


	//���������
	QOpenGLShaderProgram programTexture;
	QOpenGLShaderProgram programColor;

	//��ͼ���δ�����
    GeometryEngine *geometries;

	//OpenGL�ӽǿ��Ʋ���

	//�任
    QMatrix4x4 m_projection;

	//��¼���ʱ���������λ��
    QPointF m_lastLeftPos;
	QPointF m_lastRightPos;

	//
	int m_width;
	int m_height;

	//�ӽ�λ��
	float m_fDis;
	float m_fHeight;

	//�������
	int m_zoomType;
	void MapZoom(QPointF tempPoint, float para);		//���ŵ�ͼ

	//��ת���
	int m_rotateX;	//��ת���ĵ�X����
	int m_rotateY;	//ѡ�����ĵ�Y����
	float m_fAxisX;		//
	float m_fAxisY;		//ˮƽ����ת�Ƕ�-����
	float m_fAxisXOld;
	float m_fAxisYOld;	//ˮƽ����ת�Ƕ�-��
	void MapRotate(QPointF tempPoint, float para);	//��ת��ͼ

	//
	float m_sumX;
	float m_sumY;
	float m_paraHigh;
	int m_sumFactor;	//��ͼ�Ŵ�ϵ������λ��0.1����Ƭ��ͼ���ŵȼ���

	//ƫ�����
	float m_fPiasX;
	float m_fPiasY;
	float m_fPiasRotateX;
	float m_fPiasRotateY;
	void MapDrag(QVector2D diff);					//��ͼƽ��

	//��ʱ�ַ���
	QString m_sStr;

	//��̬���ɰ�ť
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
	//ʹ�õ������߳���Ϊ��ʱ��
	int m_fMark;	//OpenGL������´�������
	TimerThread *m_pTimerThreadForOpenGL;	//OpenGL������¼�ʱ��
	TimerThread *m_pTimerForTouch;	//��ʱ����صĴ��ز����жϼ�ʱ��

	//��ͼ��ʾģʽ(0Ϊ3Dģʽ��1Ϊ2Dģʽ��
	int m_bOpenGLMode;

	//��ͼ������
	MapCalc *m_mapCalc;

	//OpenGL����ϵԭ��λ��
	double m_centerLat; //ά��
	double m_centerLng; //����

	//���ڼ��ص�ͼ�����Ͻǵ�ī����ͶӰ����
	double m_tlMkLat;
	double m_tlMkLng;

	//��ǰ��ͼ�ȼ�
	int m_curMapLevel;

	//��ǰ��ͼ����λ�ö�Ӧ����Ƭ��ͼ��������������λ��
	int m_tx;
	int m_ty;
	int m_ppx;
	int m_ppy;

	//
	int m_downloadTimes;	//����ˢ�������ڴ�����ͼ���������
	void LoadMapData();
	void LoadMapMethod(int level, int tx, int ty, int start, int end, float z = 0);
	int LoadOnePic(int level, int tx, int ty, bool isCreateNew,float z = 0);	//����һ�ŵ�ͼ

	//
	void ResetCenterPos();

	//��ͼ����
	float GetWeightFromHeight(float height);	//��OpenGL�ӽǸ߶�Ϊheight������£�ÿ�����ض�Ӧ��OpenGL��λ
	float GetHighWeightFromLevel(int level);	//

	float GetHeightFromWeight(float weight);	//����ÿ�����ض�Ӧ��OpenGL��λ������OpenGL�ӽǸ߶�height
	float GetHeightFromLevel(int level);		//

	int GetLevelFromHeight(float height);		//

	//OpenCV����
	cv::VideoCapture g_pCapture;

	//����ʶ��
	bool m_isSR;
	HANDLE m_srHandle;
	SRComThread *m_recvThread;
	SpeechYZS *m_pSpeechYZS;

	//�����ϳ�
	TextToSpeech *m_textToSpeech;
	
	//
	HotasThread *m_pHotasThread;
	int m_hotasButtonState;

	//�������
	//NativeEventFilterZ *m_pw;
	float m_speed;
	QPointF m_swipeDirection;
	QPointF m_swipePrePoint;
	QPointF m_swipePostPoint;
	QPointF m_oldPoint;			//���ڼ�¼�ɵ�
	QPointF m_oldPoint2;
	QPointF m_pressPoint;		//���ڼ�¼��ָ���º���λ�ñ仯�ĵ�
	int m_touchPointNum;		//��ǰ���ص������
	int m_touchLongPressTimes;	//�����жϴ��س����Ĵ���
	bool m_bIsBeginTouch;		//�Ƿ�ʼ����
	bool m_bIsTouchChange;		//�Ƿ���д��صĶ���
	bool m_bIsTouchLeave;		//�Ƿ�ǰû�д��ض���
	bool m_bIsSecondPointDrag;	//�ж��Ƿ����ɴ����¼�������������϶��¼���������϶�
	bool m_bIsTouchValid;		//�жϴ��ص��ᴥ�ж��Ƿ���Ч
	bool m_bIsStartCalcTap;		//��ʼ�����ᴥ�����ж�
	void UpdateTouchState();
	void CalcSwipe(QPointF point1, QPointF point2);	//��ɨ����
	WPARAM a_WParam2=0;
	LPARAM a_LParam2=0;
	//��ȡϵͳ������Ϣ
	virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE;
	//��������
	LongPressFlag *m_pLongPressFlag;

	void SetLongPressPos(int x, int y);
	void SetLongPressPercent(float value);

	//��㷴��
	TouchPointFlag *m_pTouchPointFlag[MAX_TOUCH_NUM];
	void ClearFigurePos();
	void ShowFigurePos(QPointF point, int index);

	//�ʷ����¼�������
	bool OnLButtonDown(int x, int y);
	bool OnLButtonUp(int x, int y);
	bool OnMouseMove(int x, int y);
	bool OnMouseWheel(int x, int y, short zDelta);

	//�Զ������ݶ���
	ShapedData *m_pShapedData;
	
	//�Զ���ؼ���VAPS�����д�Ϊ��ͬ��VAPS�ؼ����ɲ�ͬ�Ķ���
	VAPS* m_vaps1;
	VAPS* m_vaps2;
	VAPS* m_vaps3;
	VAPS* m_vaps4;
	VapsMsg *m_vapsMsgRecv;
	VapsMsg *m_vapsMsgSend;
	VapsMsg *m_vapsMsgRecv2;
	VapsMsg *m_vapsMsgSend2;
	
	//�Զ���ؼ���QT��
	QFanShaped *m_pFanShaped;
	QTitle *m_pTitle;
	QFirstMenu *m_pFirstMenu;
	QTargetPosInfo *m_pTargetPosInfo;
	QStopWindow *m_pStopWindow;


	

	//TCPЭ�� ����ʶ��ģ��
	TCP  tcp_connect;                       //����������ַ��sin������
	//saClient�����ӹ㲥��ַ������Ϣ
	char tcp_cRecvBuff[800]; 
	
	int tcp_nSize, tcp_nbSize;


	//UDPЭ�� sd�澯ģ��
	WSADATA threed_wsaData;      
	//ָ��WinSocket��Ϣ�ṹ��ָ��
	WSADATA threed_wsaData2;
	SOCKET threed_sockListener;
	SOCKET threed_sockListener2;
	
	SOCKADDR_IN m_localAddr;
	SOCKADDR_IN threed_sin2, threed_saClient;                          //����������ַ��sin������
	//saClient�����ӹ㲥��ַ������Ϣ
	char threed_cRecvBuff[20];
	char threed_cSendBuff[20];
	char threed_cSendBuff2[128];
	 //������ջ�����//������ջ�����
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
	//�Զ���ؼ���QPainter��
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
	//����ͳһ����
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

	//�����Ĺ����д�˼����Ϊ���ӵ������������Ӧ������������ʾ����ǰ��״̬��
    ENUM_CONTEXT m_context;	//��ǰ�����Ľ׶�
	ENUM_CONTEXT m_oldContext;
	
	void *m_pActiveObject;		//��ǰ���ڱ��������ʾ���
	void *m_pLastActiveObject;	//��ǰ���ڱ��������ʾ���

	//�ʷ�ԭ�ﴦ��
	MorphologyInput *m_pMorInput;
	
	//�Բ�ͬ�׶ε�����ƺ�������������ɶ���
	void HandleAPPEntry(Primitive *pri);
	void HandleMapFree(Primitive *pri);
	void HandleMapMark(Primitive *pri);
	void HandleMapSearch(Primitive *pri);
	void HandleMapFanShaped(Primitive *pri);
	void HandleMapAction(Primitive *pri);
	void HandleMapHLD(Primitive *pri);
	void HandleMapBJHLD(Primitive *pri);
	//���ݱ�ǵ������λ�ñ仯�����±�ǵ�ľ�γ��λ��
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
	
	
	//�����¼�
	void onTouchFirstPress(QPointF point);					//������ʼ��
	void onTouchLastLeave();								//���ؽ���
	void onTouchTap(QPointF point);							//�ᴥ
	void onTouchDrag(QPointF prePoint, QPointF postPoint);	//��ק
	void onTouchRotate(QPointF point, float para);			//��ת
	void onTouchZoom(QPointF point, float para);			//����
	void onTouchLongPress(QPointF point, int timeMs);		//����
	void onTouchSwipe(QPointF prePoint, QPointF postPoint);	//��ɨ
	void onTouchDTap(QPointF point);						//˫�ᴥ
	//void getCP(WPARAM a_WParam, LPARAM a_LParam);//�ֶ�����
	//����¼�  
	void onMousePress(QPointF point);

	void onMouseRelease(QPointF point);
	void onMouseDblClick(QPointF point);
	void onMouseMove(QPointF prePoint, QPointF postPoint);

	//�����¼�
	void onMouseWheel(QPointF point, float para);




	//���������¼�
	void onStartSR();
	void onStopSR();
	void HandleSRResult(QString);
	
	int GetNumFromSRResult(QString);

	//�����¼�
	//void onKeyEvent(QEvent* ev);

	//���ն�ͨ�����ƵĽ������ִ����Ӧ����
	//void onMultiChannelCtrl();

	//���õ�ͼ��ת�Ƕ�
	void onResetAlpha();

	//���õ�ͼ����λ�õ�����λ��
	void onResetLocation();

	//����һ�����ܲ˵���ʾ�������Ϣ
	void onSetMode(int mode);		//�õ�����ģʽ

	//���������˵���ʾ�������Ϣ
	void onSetSearchType(int type);

	//���ձ�ǵ���ʾ�������Ϣ
	void onMapMarkPointDrag(QPointF, QPointF);
	void onMapMarkPointDrag2(QPointF, QPointF);
	//���������������ݶ������Ϣ
	void onShapedDataChangeLat(float lat);
	void onShapedDataChangeLng(float lng);
	void onShapedDataChangeMKLat(float mkLat);
	void onShapedDataChangeMKLng(float mkLng);
	void onShapedDataChangeStartAngle(float startAngle);
	void onShapedDataChangeSpanAngle(float spanAngle);
	void onShapedDataChangeDis(float dis);
	void onShapedDataChangeDirection(int direction);

	//������������ͼ�ε���Ϣ
	void onShapedSectionAdjustStartAngle(float startAngle);
	void onShapedSectionAdjustSpanAngle(float spanAngle);
	void onShapedSectionAdjustRadius(float pxDis);
	void onShapedSectionReversalDirection();

	//�������β������ÿ����Ϣ
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
	//����ֹͣ�����������Ϣ
	void onEditSearch();
	void onStopSearch();

	//�ʷ�ԭ�ﴦ��
	void onHandlePrimitive(Primitive* pri);

	//
	void onGetJoyData(JOYINFOEX*);
	void onGetJoyState(int);
	
	
private:
	float square(const double num);
	float TwoPtDistance(const QPointF &pt1, const QPointF &pt2);
};

#endif // OPENGL_H

