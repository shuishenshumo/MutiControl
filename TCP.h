#ifndef TCP_H
#define TCP_H

#define NET_BUF_SIZE (10240)

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <QWidget>
#include<QString>
#pragma comment(lib, "ws2_32.lib")

//连接TCP网络
DWORD WINAPI  TCPConAsServer(LPVOID lpParameter);
DWORD WINAPI  TCPConAsClient(LPVOID lpParameter);
extern DWORD WINAPI  TCPReceive(LPVOID lpParameter);
class TCP :public QObject
{
	Q_OBJECT
private:

public:
	TCP();
	~TCP();

	sockaddr_in m_localAddr;
	sockaddr_in m_remoteAddr;
	int m_nAddrLen;
	//volatile 
	int m_kind;//1表示server，2表示client
	HANDLE m_connectThread;
	
	//数据缓冲
	int m_recvDataLen;
	int m_sendDataLen;
	char m_recvData[NET_BUF_SIZE];
	char m_sendData[NET_BUF_SIZE];

	int TCPInit();
	int TCPFree();
	int TCPConAsSer(int port);
	int TCPConAsCli(int port, char *ipAddr);

	int CreateConThread();

	int GetConState();

	int SendData();
	int RecvData();
	int GetRecvBuf(char *buf);
	int SetSendBuf(char *buf, int len);
signals:
	void recvResult(QString);
};

#endif

