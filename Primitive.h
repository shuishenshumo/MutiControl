#ifndef PRIMITIVE_H
#define PRIMITIVE_H

//--------------------------------------------------



//--------------------------------------------------

//�ʷ���ԭ��
typedef enum 
{
	//-----------����¼�--------------//

	//windows����ϵͳ���Զ�����ָ����ת��Ϊ����������������¼�
	MOUSE_LEFT_DOWN,	//
	MOUSE_LEFT_MOVE,		//
	MOUSE_LEFT_RELEASE,		//
MOUSE_LEFT_DCLICK,		//

//-----------�����¼�--------------//

//�������¼�
WHEEL = 100,

//���д����������¼�
TOUCH_PRESS = 200,		//���ؿ�ʼ�¼���������ز���ʼ��ֻ�е�ָ�������򲻽��봥�ع��̣���˲��ᴥ�����ؽ����¼�
TOUCH_LEAVE,			//���ؽ����¼����Ӵ��ع��̵����һ����ָ�뿪
TOUCH_TAP,				//�ᴥ
TOUCH_DRAG,				//��ק
TOUCH_ROTATE,			//��ת
TOUCH_ZOOM,				//����
TOUCH_LONG_PRESS,		//����
TOUCH_SWIPE,			//��ɨ

//---------�Զ����ڲ��¼�----------//

//
PAGE_ZH = 1000,


//һ�����ܲ˵�
SWITCH_JY,			//��Ԯ
SWITCH_ZF,			//ֱ��
SWITCH_SS,			//

SWITCH_XT,			//Эͬ

//�������Ͳ˵�
SEARCH_SX,			//��������
SEARCH_PT,			//����������
SEARCH_HX,			//��������

//
SX_ACTION,			//ִ������
SX_CANCEL,			//�˳��ƻ�

//
EDIT_SEARCH,		//�༭����
STOP_SEARCH,		//ֹͣ����

//
MAIN_MENU,

//
FUNC_MENU,

//
MAP_MODE,

//��������
SWITCH_DIRECTION,
CHANGE_CLOCK,
CHANGE_ANTI_CLOCK,

//��γ��
OPEN_LAT,
OPEN_LNG,
CHANGE_NORTH,
CHANGE_SOUTH,
CHANGE_EAST,
CHANGE_WEST,
INPUT_LAT,
INPUT_LNG,

//��ʼ����
OPEN_ANGLE,
INPUT_ANGLE,

//����Ƕ�
OPEN_SPAN,
INPUT_SPAN,

//�����뾶
OPEN_DIS,
INPUT_DIS,

//����
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

//ָ��
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

	//---------�����кܶ��ڲ��¼�������ȡ������----------//

}PRI_TYPE;

//�����
typedef struct 
{
	int x;
	int y;
}PriPoint;

//��ק����
typedef struct
{
	PriPoint p1;
	PriPoint p2;
}PriDragPara;

//��ת����
typedef struct
{
	PriPoint p1;
	float angle;
}PriRotatePara;

//���Ų���
typedef struct
{
	PriPoint p1;
	float multiple;
}PriZoomPara;

//��������
typedef struct
{
	PriPoint p1;
	int time;
}PriLongPress;

//--------------------------------------------------


//�������õ��ĵ��һ����ڹ���

//����ʶ�����еĲ�����ʾ
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

//�ʷ�ԭ��ṹ��
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
	MAP_FREE,		//��ͼ�������ν׶�
	MAP_MARK,		//ѡ�е�ͼ�ϵ�ĳ��Ŀ��㣬����ʾһ��������
	MAP_SEARCH,		//��ĳ��Ŀ���Ϊ���ģ�����������
	MAP_FAN_SHAPED,	//��ĳ��Ŀ���Ϊ���ģ����������������ã�֧��ͼ�β����Ͳ��������������÷�ʽ��
	MAP_ACTION,//ִ�����������׶�
	MAP_BJHLD,		
	MAP_HLD
}ENUM_CONTEXT;


//Ӧ�ýӿ�
typedef enum
{
	
}APP_INT;


#endif