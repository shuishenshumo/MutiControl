#pragma once

#include <QTimer>
#include <QTimerEvent>

#include "CircularQueue.h"
#include "netconnthread.h"

//
#define VAPS_UDP_Port (6001)
#define VPAS_UDP_IP ("127.0.0.1")

//

//������������
typedef enum
{
	TCP_SERVER = 0,
	TCP_CLIENT = 1,
	UDP_SERVER = 2,
	UDP_CLIENT = 3,
	DDS_TYPE,
	OTHERS_TYPE
}CONN_TYPE;

//VAPSͨѶ��ʽ
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

	//�豸��������
	CONN_TYPE m_eType;

	//�����������ݵ�ѭ�����л���ռ�
	CircularQueue m_circularQueue;

	void SetConnState(int state);

	//
	NetConnThread *m_conn;
	int m_connState;

private:
	void InitPara();
	void InitConn();
	void CloseConn();

	//������Ϣ���մ���
	void MessageProc();

	void SendData(VapsMessage msg, int len, int value);

	//
	int m_timerId;
	void timerEvent(QTimerEvent *event);

public slots:
	//�������紦���̵߳�������Ϣ
	void slotDataReceived(char *data, int len);

	//�������紦���̵߳�����״̬
	void slotConnState(int state);

signals:
	//���͸����紦���߳�
	void sigSendData(char*, int);

	//���͸���������
	void sigStateChange(int);
};

