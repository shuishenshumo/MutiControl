#ifndef HOTASTHREAD_H
#define HOTASTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include <windows.h>
#include <Mmsystem.h>


class HotasThread : public QThread
{
	Q_OBJECT

public:
	HotasThread(QObject *parent = 0);
	~HotasThread();

	void run() Q_DECL_OVERRIDE;

	void stop();

	bool m_valid;
	bool m_run;

signals:
	void sigJoyData(JOYINFOEX*);
	void sigJoyState(int);
};


#endif // HotasThread_H