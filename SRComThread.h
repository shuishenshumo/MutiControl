#ifndef SRRRECVTHREAD_H
#define SRRRECVTHREAD_H

#include <windows.h>
#include <QThread>
#include <QString>

#define MAX_BUF_SIZE (1000000)

class SRComThread : public QThread
{
	Q_OBJECT

public:
	SRComThread(QObject *parent);
	~SRComThread();

	void stop();

	void startSR();
	void stopSR();
	void quitSR();
protected:
	void run();
private:
	volatile bool stopped;

public slots:

signals:
	void recvResult(QString);
};

#endif // MYTHREAD_H
