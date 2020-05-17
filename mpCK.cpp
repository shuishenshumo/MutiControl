#include "mpCK.h"
#include "opengl.h"
#include <QTime>
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif
#ifdef _cplusplus
extern "C"{
#endif
	ENUM_CONTEXT m_context;	//当前所处的阶段
#ifdef _cplusplus
}
#endif


WPARAM a_WParam=0;
LPARAM a_LParam=0;
NativeEventFilterZ::NativeEventFilterZ() 
{
	/*qtime = new QTime();
	qtime->start();
	if (qtime->elapsed() >= 33)
	{
		m_context2 = m_context;
		m_oldContext2 = m_oldContext;
		qtime->restart();
	}*/

}

NativeEventFilterZ::~NativeEventFilterZ()
{
	/*
	if (msg != NULL)
	{
		delete msg;
	}
	*/

}
bool NativeEventFilterZ::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
	MSG* pMsg = reinterpret_cast<MSG*>(message);
	MSG *msg = pMsg;
	
	
	if (m_context == MAP_FREE&&msg->message == WM_TOUCH)
	{
		qDebug() << m_context;
			a_WParam = msg->wParam;
			a_LParam = msg->lParam;
			qDebug() << a_WParam;
			qDebug() << a_LParam;
			emit sigmsg(a_WParam, a_LParam);
			return true;
	}	
	else
	{   
		
		return false;
	}
	
		
}
void  NativeEventFilterZ::start()
{  
	if (a_WParam != 0)
	{
		
	}
}