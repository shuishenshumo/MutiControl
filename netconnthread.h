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

	//����״̬
	int m_connectState;

	//�����������ԣ���������
	void setConn(int port, char *ipAddr = NULL);

	//�رո��߳�
	void stop();

	void setConnState(int state);

	//
	int m_isSpecial;
	void SetSpecial();

protected:
	void run();	//��ѭ����

private:
	volatile bool stopped;	//threadֹͣ���

public slots:
	void slotDataReceived(char *data, int len);	//�յ�������������Ϣ��ͨ�����緢�����ӷ�

signals:
	void sigSendData(char*, int);	//�յ�������Ϣ�󣬷���������
	void sigStateChange(int);		//��������״̬�����ı�󣬷���������
};

#endif // TCPCONNTHREAD_H
