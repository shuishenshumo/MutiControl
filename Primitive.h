#ifndef PRIMITIVE_H
#define PRIMITIVE_H

//--------------------------------------------------



//--------------------------------------------------

//词法层原语
typedef enum 
{
	//-----------鼠标事件--------------//

	//windows操作系统会自动将单指操作转换为鼠标左键引发的相关事件
	MOUSE_LEFT_DOWN,	//
	MOUSE_LEFT_MOVE,		//
	MOUSE_LEFT_RELEASE,		//
MOUSE_LEFT_DCLICK,		//

//-----------滚轮事件--------------//

//鼠标滚轮事件
WHEEL = 100,

//具有触控特征的事件
TOUCH_PRESS = 200,		//触控开始事件，如果触控操作始终只有单指操作，则不进入触控过程，因此不会触发触控结束事件
TOUCH_LEAVE,			//触控结束事件，从触控过程到最后一根手指离开
TOUCH_TAP,				//轻触
TOUCH_DRAG,				//拖拽
TOUCH_ROTATE,			//旋转
TOUCH_ZOOM,				//缩放
TOUCH_LONG_PRESS,		//长按
TOUCH_SWIPE,			//轻扫

//---------自定义内部事件----------//

//
PAGE_ZH = 1000,


//一级功能菜单
SWITCH_JY,			//救援
SWITCH_ZF,			//直飞
SWITCH_SS,			//

SWITCH_XT,			//协同

//搜索类型菜单
SEARCH_SX,			//扇形搜索
SEARCH_PT,			//爬梯形搜索
SEARCH_HX,			//盒形搜索

//
SX_ACTION,			//执行搜索
SX_CANCEL,			//退出计划

//
EDIT_SEARCH,		//编辑搜索
STOP_SEARCH,		//停止搜索

//
MAIN_MENU,

//
FUNC_MENU,

//
MAP_MODE,

//搜索方向
SWITCH_DIRECTION,
CHANGE_CLOCK,
CHANGE_ANTI_CLOCK,

//经纬度
OPEN_LAT,
OPEN_LNG,
CHANGE_NORTH,
CHANGE_SOUTH,
CHANGE_EAST,
CHANGE_WEST,
INPUT_LAT,
INPUT_LNG,

//初始航向
OPEN_ANGLE,
INPUT_ANGLE,

//扇面角度
OPEN_SPAN,
INPUT_SPAN,

//搜索半径
OPEN_DIS,
INPUT_DIS,

//参数
PRI_NUM_0,
PRI_NUM_1,
PRI_NUM_2,
PRI_NUM_3,
PRI_NUM_4,
PRI_NUM_5,
PRI_NUM_6,
PRI_NUM_7,
PRI_NUM_8,
PRI_NUM_9,
PRI_NUM_POINT,
PRI_DEGREE,
PRI_MIN,
PRI_SEC,

//指令
NORMAL_COMFIRM,
NORMAL_CANCEL,
NORMAL_CLEAR,
NORMAL_BACK,
Confirm1,
	//
	VAPS_XT,
	VAPS_TCXT,
	VAPS_DH,
	VAPS_FC,
	VAPS_GD,
	VAPS_BJDJ,
	VAPS_TCDJ,
	VAPS_WQ,
	VAPS_FTK,
	VAPS_KD,
	VAPS_TS,
	VAPS_ZW,
	VAPS_BD,
	VAPS_ZJM,
	VAPS_FTMS,
	VAPS_KDMS,
	VAPS_JJMS,

	//---------（还有很多内部事件可以提取出来）----------//

}PRI_TYPE;

//点参数
typedef struct 
{
	int x;
	int y;
}PriPoint;

//拖拽参数
typedef struct
{
	PriPoint p1;
	PriPoint p2;
}PriDragPara;

//旋转参数
typedef struct
{
	PriPoint p1;
	float angle;
}PriRotatePara;

//缩放参数
typedef struct
{
	PriPoint p1;
	float multiple;
}PriZoomPara;

//长按参数
typedef struct
{
	PriPoint p1;
	int time;
}PriLongPress;

//--------------------------------------------------


//把所有用到的点放一起便于管理

//语音识别结果中的参数表示
typedef enum
{
	SR_NONE = -1,
	SR_0,
	SR_1,
	SR_2,
	SR_3,
	SR_4,
	SR_5,
	SR_6,
	SR_7,
	SR_8,
	SR_9,
	SR_POINT,
	SR_DEGREE,
	SR_MIN,
	SR_SEC
}ENUM_SR_PARA;

//--------------------------------------------------

//词法原语结构体
typedef struct
{
	PRI_TYPE type;
	void* para;
}Primitive;

//--------------------------------------------------

typedef enum
{
	APP_ENTRY = 0,
	APP_ENTRY2,
	MAP_FREE,		//地图自由漫游阶段
	MAP_MARK,		//选中地图上的某个目标点，并显示一级搜索框
	MAP_SEARCH,		//以某个目标点为中心，弹出搜索框
	MAP_FAN_SHAPED,	//以某个目标点为中心，弹出扇形搜索设置（支持图形操作和参数输入两种设置方式）
	MAP_ACTION,//执行扇形搜索阶段
	MAP_BJHLD,		
	MAP_HLD
}ENUM_CONTEXT;


//应用接口
typedef enum
{
	
}APP_INT;


#endif