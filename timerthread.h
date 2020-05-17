#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QThread>
#include <qtimer.h>

class TimerThread : public QThread
{
	Q_OBJECT

public:
	TimerThread(QObject *parent);
	~TimerThread();

	void SetInterval(int time);
	void Pause();
	void Continue();

	void stop();
protected:
	void run();
	void timerEvent(QTimerEvent *e);

private:
	volatile bool m_bStopped;
	volatile bool m_bPaused;

	int m_nTimerDrawId;
	int m_nInterval;
signals:
	void sendTimerSignal();
};

#endif // TIMERTHREAD_H
