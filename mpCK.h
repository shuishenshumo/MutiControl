#ifndef MPCK_H
#define MPCK_H

#include <QDebug>
#include <qabstractnativeeventfilter.h>
#include <QWidget>
#include <QThread>
#include <windows.h>
#pragma comment(lib, "user32.lib")



class NativeEventFilterZ : public QObject, public QAbstractNativeEventFilter
{
Q_OBJECT
public:
	NativeEventFilterZ();
	~NativeEventFilterZ();
	QTime *qtime;
	//MSG *msg;
	//²¶×½windows´¥¿ØÏûÏ¢WM_TOUCH
	void start();
	virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE;
signals:
	void sigmsg(WPARAM,LPARAM);
};
#endif // CLASSNATIVEEVENTFILTERZ_H