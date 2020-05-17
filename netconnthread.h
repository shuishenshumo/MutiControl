#ifndef TCPCONNTHREAD_H
#define TCPCONNTHREAD_H

#include <QThread>
#include <QDateTime>
#include "TCP.h"
#include "UDP.h"

#define TCP_CONN (0)
#define UDP_CONN (1)

#define MAX_DELAY_TIMES (100000)

class NetConnThread : public QThread
{
	Q_OBJECT

public:
	NetConnThread(QObject *parent, int type);
	~NetConnThread();

	int m_type;	//0-TCP, 1-UDP

	int m_connCtrl;

	//
	TCP *m_pTCP;
	UDP *m_pUDP;

	int m_port;
	char m_ipStr[20];

	//
	int m_dateTime;
	QDateTime m_qDateTime;

	//连接状态
	int m_connectState;

	//设置连接属性，进行连接
	void setConn(int port, char *ipAddr = NULL);

	//关闭该线程
	void stop();

	void setConnState(int state);

	//
	int m_isSpecial;
	void SetSpecial();

protected:
	void run();	//主循环体

private:
	volatile bool stopped;	//thread停止标记

public slots:
	void slotDataReceived(char *data, int len);	//收到父对象发来的消息，通过网络发给连接方

signals:
	void sigSendData(char*, int);	//收到网络消息后，发给父对象
	void sigStateChange(int);		//网络连接状态发生改变后，发给父对象
};

#endif // TCPCONNTHREAD_H
