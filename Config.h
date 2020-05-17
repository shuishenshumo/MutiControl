#ifndef CONFIG_H
#define CONFIG_H

//------------------------------------------------------------------

#define MAP_SIZE (256)	//每张瓦片地图默认256×256像素大小

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

//OpenGL画面更新周期(ms)
#define REFRESH_TIME (20)

//------------------------------------------------------------------

//
#define M_PI (3.14159265358979323846)	//PI
#define EARTH_PERIMETER (20037508.34)	//地球周长一半
#define EARTH_RADIUS (6378137)			//地球半径

//庞海龙提供的水平角、距离与经纬度互转的程序中使用的地球参数
#define NAV_Ea (6378137.0)
#define NAV_Eb (6356752.3142)

//------------------------------------------------------------------

//地图纹理相关参数
#define MIN_MAP_LEVEL (4)	//加载最小地图等级
#define MAX_MAP_LEVEL (16)	//加载最大地图等级

#define INIT_MAP_LEVEL (9)	//初始地图等级（不能小于9，因为当前计算机制下，当OpenGL视角高度低于某个阈值，整个画面就没有了）

#define CIRCLE_NUM (9)		//循环加载圈数

#define JUXING_SIZE (16)	//判断单次需加载图片的边长图片数量

#define DOWNLOAD_TIMES (9)	//每个刷新周期加载地图数量

#define DOWNLOAD_TIMES_2 (1)	//每个刷新周期加载地图数量

#define WHEEL_ZOOM_STEP (0.2)		//滚轮缩放程度

#define NULL_MAP_PATH ("null.png")	//瓦片地图不存在时使用

//------------------------------------------------------------------

#define TOUCH_AREA_RADIUS (25)

#define TOUCH_ROTATE_LIMIT (5)	//触控旋转操作的阈值角度

#define TOUCH_ZOOM_LIMIT (5)	//触控缩放操作的阈值像素

#define TOUCH_ZOOM_STEP (1)		//滚轮缩放程度（单位0.1）

#define TOUCH_TAP_MAX_TIME (0.3)

#define LONG_PRESS_CIRCLE_RADIUS (30)	//长按操作相关
#define LONG_PRESS_MIN_TIME (0.5)
#define LONG_PRESS_MAX_TIME (2)
#define LONG_PRESS_MAX_HOLD_TIME (4)

#define TOUCH_REFRESH_TIME (5)		//触控状态判断周期

#define MAX_TOUCH_NUM (10)

#define TOUCH_SWIPE_LIMIT (20)

//------------------------------------------------------------------

#endif