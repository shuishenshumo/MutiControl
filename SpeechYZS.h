#ifndef SPEECHYZS_H
#define SPEECHYZS_H

#include <QWidget>
#include <qstring.h>
#include <windows.h>
#include <QTime>
#include"TCP.h"
class SpeechYZS : public QObject
{
	Q_OBJECT

public:
	SpeechYZS();
	~SpeechYZS();
	char tcp_cRecvBuff[50];
	TCP  tcp_connect;
	void Init();
	void Release();
	void StartSR();
	void StopSR();
	QString getChinese(QString str);
	QTime time;

private:
	bool m_isLoaded;
signals:
	void recvResult(QString);
};

#endif