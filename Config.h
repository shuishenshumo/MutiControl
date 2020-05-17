#ifndef CONFIG_H
#define CONFIG_H

//------------------------------------------------------------------

#define MAP_SIZE (256)	//ÿ����Ƭ��ͼĬ��256��256���ش�С

//------------------------------------------------------------------

#define MAP_PIC_PATH ("D:\Shared\ForShow_3_0_yunzhisheng\SwatFly_final\bin\Resource\ShangHai.jpg")
#define MAP_MIN_X (27388)//
#define MAP_MAX_X (27492)//
#define MAP_MIN_Y (13371)//
#define MAP_MAX_Y (13455)//
#define ZOOM_LEVEL (15)

//
#define MAP_X_NUM (MAP_MAX_X-MAP_MIN_X+1)
#define MAP_Y_NUM (MAP_MAX_Y-MAP_MIN_Y+1)

#define MAP_X_PIX (MAP_X_NUM*MAP_SIZE)
#define MAP_Y_PIX (MAP_Y_NUM*MAP_SIZE)

//------------------------------------------------------------------
	
#define MAP_PATH_PRE_11_16 ("D:/Shared/satellite")
#define PATH_11_16_MIN (11)
#define PATH_11_16_MAX (16)

//#define MAP_PATH_PRE_0_10 ("D:/apache-tomcat-8.5.4/webapps/ROOT/map-data/terrain")
//#define MAP_PATH_PRE_0_10 ("D:/apache-tomcat-8.5.4/webapps/ROOT/map-data/satellite")
//#define MAP_PATH_PRE_0_10 ("C:/I-DECK/webserver/apache-tomcat-8.5.4/webapps/ROOT/map-data/satellite")
#define MAP_PATH_PRE_0_10 ("D:/Shared/satellite")
#define PATH_0_10_MIN (0)
#define PATH_0_10_MAX (10)

#define MAP_LIGHT_PRE ("D:/apache-tomcat-8.5.4/webapps/ROOT/map-data/light")

//------------------------------------------------------------------

//OpenGL�����������(ms)
#define REFRESH_TIME (20)

//------------------------------------------------------------------

//
#define M_PI (3.14159265358979323846)	//PI
#define EARTH_PERIMETER (20037508.34)	//�����ܳ�һ��
#define EARTH_RADIUS (6378137)			//����뾶

//�Ӻ����ṩ��ˮƽ�ǡ������뾭γ�Ȼ�ת�ĳ�����ʹ�õĵ������
#define NAV_Ea (6378137.0)
#define NAV_Eb (6356752.3142)

//------------------------------------------------------------------

//��ͼ������ز���
#define MIN_MAP_LEVEL (4)	//������С��ͼ�ȼ�
#define MAX_MAP_LEVEL (16)	//��������ͼ�ȼ�

#define INIT_MAP_LEVEL (9)	//��ʼ��ͼ�ȼ�������С��9����Ϊ��ǰ��������£���OpenGL�ӽǸ߶ȵ���ĳ����ֵ�����������û���ˣ�

#define CIRCLE_NUM (9)		//ѭ������Ȧ��

#define JUXING_SIZE (16)	//�жϵ��������ͼƬ�ı߳�ͼƬ����

#define DOWNLOAD_TIMES (9)	//ÿ��ˢ�����ڼ��ص�ͼ����

#define DOWNLOAD_TIMES_2 (1)	//ÿ��ˢ�����ڼ��ص�ͼ����

#define WHEEL_ZOOM_STEP (0.2)		//�������ų̶�

#define NULL_MAP_PATH ("null.png")	//��Ƭ��ͼ������ʱʹ��

//------------------------------------------------------------------

#define TOUCH_AREA_RADIUS (25)

#define TOUCH_ROTATE_LIMIT (5)	//������ת��������ֵ�Ƕ�

#define TOUCH_ZOOM_LIMIT (5)	//�������Ų�������ֵ����

#define TOUCH_ZOOM_STEP (1)		//�������ų̶ȣ���λ0.1��

#define TOUCH_TAP_MAX_TIME (0.3)

#define LONG_PRESS_CIRCLE_RADIUS (30)	//�����������
#define LONG_PRESS_MIN_TIME (0.5)
#define LONG_PRESS_MAX_TIME (2)
#define LONG_PRESS_MAX_HOLD_TIME (4)

#define TOUCH_REFRESH_TIME (5)		//����״̬�ж�����

#define MAX_TOUCH_NUM (10)

#define TOUCH_SWIPE_LIMIT (20)

//------------------------------------------------------------------

#endif