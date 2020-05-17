#pragma once

#include <QTimer>
#include <QTimerEvent>

#include "CircularQueue.h"
#include "netconnthread.h"

//
#define VAPS_UDP_Port (6001)
#define VPAS_UDP_IP ("127.0.0.1")

//

//网络连接类型
typedef enum
{
	TCP_SERVER = 0,
	TCP_CLIENT = 1,
	UDP_SERVER = 2,
	UDP_CLIENT = 3,
	DDS_TYPE,
	OTHERS_TYPE
}CONN_TYPE;

//VAPS通讯格式
typedef struct VapsMessage
{
	char ddName[32];
	char bufName[32];
	char dataLen[4];
	char data[4];
}VapsMessage;

class TestVAPS : public QObject
{
	Q_OBJECT

public:
	TestVAPS(void);
	~TestVAPS(void);

	//设备连接类型
	CONN_TYPE m_eType;

	//接收网络数据的循环队列缓冲空间
	CircularQueue m_circularQueue;

	void SetConnState(int state);

	//
	NetConnThread *m_conn;
	int m_connState;

private:
	void InitPara();
	void InitConn();
	void CloseConn();

	//网络消息接收处理
	void MessageProc();

	void SendData(VapsMessage msg, int len, int value);

	//
	int m_timerId;
	void timerEvent(QTimerEvent *event);

public slots:
	//接收网络处理线程的网络消息
	void slotDataReceived(char *data, int len);

	//接收网络处理线程的连接状态
	void slotConnState(int state);

signals:
	//发送给网络处理线程
	void sigSendData(char*, int);

	//发送给其他对象
	void sigStateChange(int);
};

