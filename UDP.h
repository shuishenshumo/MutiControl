#ifndef UDP_H
#define UDP_H

#define NET_BUF_SIZE (10240)

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")

class UDP
{
private:

public:
	UDP();
	~UDP();

	SOCKET m_socket;
	sockaddr_in m_localAddr;
	sockaddr_in m_remoteAddr;
	int m_nAddrLen;

	//Êý¾Ý»º³å
	int m_recvDataLen;
	int m_sendDataLen;
	char m_recvData[NET_BUF_SIZE];
	char m_sendData[NET_BUF_SIZE];

	int UDPInit();
	int UDPFree();
	int UDPConAsSer(int port);
	int UDPConAsCli(int port, char *ipAddr);
	int SendData();
	int RecvData();
	int GetRecvBuf(char *buf);
	int SetSendBuf(char *buf, int len);

	void CloseSocket();
};

#endif