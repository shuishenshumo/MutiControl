#pragma once

#include <QObject>

#include <QString>
#include <QStringList>

#include <windows.h>


#include "vxtPLBasicTypes.h"
#include "vxtRTDrawingIntegrationI.h"

#include <map>

using namespace std;

typedef vxtRTDrawingIntegrationI* (*fCreateTopIntegrator)();
typedef vxtRTDrawingIntegration_V2I* (*fCreateTopIntegrator_V2)();
typedef vxtRTDrawingIntegration_V3I* (*fCreateTopIntegrator_V3)();
typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;

#include "Point3D.h"
struct HudStruct
{
	vxtDouble latitude;
	vxtDouble longitude;
	vxtFloat ind_air_spd;
	vxtFloat true_air_spd;
	vxtFloat vertical_spd;
	vxtFloat ground_spd;
	vxtFloat ground_track;
	vxtFloat baro_altitude;
	vxtFloat radar_altitude;
	vxtFloat accel;
	vxtFloat vel_body_x;
	vxtFloat vel_body_y;
	vxtFloat vel_body_z;
	vxtFloat mach_number;
	vxtFloat g_load;
	vxtFloat angle_of_attack;
	vxtFloat sideslip;
	vxtFloat roll;
	vxtFloat pitch;
	vxtFloat true_heading;
	vxtFloat mag_heading;
	vxtFloat roll_rate;
	vxtFloat pitch_rate;
	vxtFloat heading_rate;
	vxtFloat total_mass;
	vxtFloat fuel_mass;
	vxtFloat fuel_mass_ratio;
	vxtFloat fuel_tank_1;
	vxtFloat fuel_tank_2;
	vxtFloat fuel_tank_3;
	vxtFloat fuel_tank_4;
	vxtUShort flap_in_transit;
	vxtUShort slat_in_transit;
	vxtUShort stall_warning;
	vxtUShort on_ground;
	vxtFloat selected_course;
	vxtFloat gear_pos_1;
	vxtFloat gear_pos_2;
	vxtFloat gear_pos_3;
	vxtFloat gear_pos_4;
	vxtFloat gear_pos_5;
	vxtFloat wheel_angle_1;
	vxtFloat wheel_angle_2;
	vxtFloat wheel_angle_3;
	vxtFloat wheel_angle_4;
	vxtFloat wheel_angle_5;
	vxtUShort gear_on_ground_1;
	vxtUShort gear_on_ground_2;
	vxtUShort gear_on_ground_3;
	vxtUShort gear_on_ground_4;
	vxtUShort gear_on_ground_5;
	vxtUShort gear_status_1;
	vxtUShort gear_status_2;
	vxtUShort gear_status_3;
	vxtUShort gear_status_4;
	vxtUShort gear_status_5;
	vxtFloat pitch_trim;
	vxtFloat roll_trim;
	vxtFloat yaw_trim;
	vxtFloat flap;
	vxtFloat flap_percent;
	vxtFloat slat;
	vxtFloat slat_percent;
	vxtFloat spoiler;
	vxtFloat spd_brake;
};

struct Float50
{
	vxtFloat float_array[50];
};

class VAPS : public QObject
{
	Q_OBJECT

public:
	VAPS(QString dllPath, QWidget *parent = 0);
	~VAPS(void);

	//
	bool m_isLoaded;

	//视窗
	float m_vapsIMin;
	float m_vapsIMax;
	float m_vapsJMin;
	float m_vapsJMax;
	vxtInt m_RenderingContextId=0;

	//链接库相关
	QString m_dllPath;
	HINSTANCE m_LoadedDLLHandle;

	//VAPS相关
	vxtRTDrawingIntegrationI*  m_pDrawingIntegration;
	vxtRTDrawingIntegration_V2I* m_pDrawingIntegration_V2;
	vxtRTDrawingIntegration_V3I* m_pDrawingIntegration_V3;

	HudStruct*                 m_pHudStruct;
	Float50*                   m_pFloat50;

	//DLL管理
	int LoadDLL(QString fileName);
	void UnLoadDLL();

	//获取VAPS中数据交换的buffer
	void *pGetBuffer(const char *a_pBufferName, unsigned int &a_rSize);
	void vUpdateBuffer(const char *a_pBufferName);

	//绘图
	void vSetRect(int iMin, int iMax, int jMin, int jMax);
	void vSetSize(int width, int height);
	void vSetPosition(int x, int y);
	void vExecuteIteration();

	//事件
	bool OnLButtonDblClk(int x, int y);
	bool OnRButtonDblClk(int x, int y);
	bool OnMButtonDblClk(int x, int y);
	bool OnLButtonDown(int x, int y);
	bool OnRButtonDown(int x, int y);
	bool OnMButtonDown(int x, int y);
	bool OnLButtonUp(int x, int y);
	bool OnRButtonUp(int x, int y);
	bool OnMButtonUp(int x, int y);
	bool OnMouseMove(int x, int y);
	bool OnMouseWheel(int x, int y, short zDelta);
	bool OnKeyDown(UINT nChar);
	bool OnChar(UINT nChar, UINT modifiers, UINT nRepCnt);
	bool OnKeyUp(UINT nChar, UINT modifiers, UINT nRepCnt);
	bool OnSysKeyDown(UINT nChar, UINT modifiers, UINT nRepCnt);
	bool OnSysChar(UINT nChar, UINT modifiers, UINT nRepCnt);
	bool OnSysKeyUp(UINT nChar, UINT modifiers, UINT nRepCnt);
	LRESULT OnTouch(HWND hwnd,WPARAM a_WParam, LPARAM a_LParam);
};