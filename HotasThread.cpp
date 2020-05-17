#include "HotasThread.h"
#include <qdebug.h>

#pragma comment(lib,"winmm.lib")

HotasThread::HotasThread(QObject *parent)
	: QThread(parent)
{
	m_run = true;
	m_valid = false;
}


HotasThread::~HotasThread()
{

}

void HotasThread::run()
{
	JOYINFO joyinfo;
	JOYINFOEX joyinfoex;
	joyinfoex.dwSize = sizeof(JOYINFOEX);
	joyinfoex.dwFlags = JOY_RETURNALL;
	while (m_run)
	{
		if (m_valid)
		{
			if (joyGetPosEx(JOYSTICKID1, &joyinfoex) == JOYERR_NOERROR)
			{
				JOYINFOEX *newJoyData = new JOYINFOEX;
				memcpy(newJoyData, &joyinfoex, sizeof(JOYINFOEX));
				emit sigJoyData(newJoyData);
			}
			else
			{
				sigJoyState(0);
				m_valid = false;
			}
		}
		else
		{
			if (joyGetNumDevs() > 0 && joyGetPos(JOYSTICKID1, &joyinfo) != JOYERR_UNPLUGGED)
			{
				/*qDebug() << "JoyStick init success!";*/
				m_valid = true;
				sigJoyState(1);
			}
		}
		msleep(50);
	}
}

void HotasThread::stop()
{
	m_run = false;
}