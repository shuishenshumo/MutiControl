#include "netconnthread.h"

NetConnThread::NetConnThread(QObject *parent, int type)
	: QThread(parent)
{
	//
	m_type = type;

	//
	stopped = false;

	//
	m_connectState = -1;

	//
	m_isSpecial = 0;

	//
	m_connCtrl = 1;

	//
	m_pTCP = NULL;
	m_pUDP = NULL;
	if (m_type == TCP_CONN)
	{
		m_pTCP = new TCP();
	}
	else if (m_type == UDP_CONN)
	{
		m_pUDP = new UDP();
	}

	//收到父对象发来的消息，并通过网络转发出去
	connect(parent, SIGNAL(sigSendData(char*, int)), this, SLOT(slotDataReceived(char*, int)));
}

NetConnThread::~NetConnThread()
{
	if (m_pTCP != NULL)
	{
		delete m_pTCP;
		m_pTCP = NULL;
	}
	if (m_pUDP != NULL)
	{
		delete m_pUDP;
		m_pUDP = NULL;
	}
}

void NetConnThread::SetSpecial()
{
	m_isSpecial = 1;
}

void NetConnThread::setConn(int port, char *ipAddr)
{
	m_port = port;
	memset(m_ipStr, 0, 20);
	if (ipAddr != NULL)
		memcpy(m_ipStr, ipAddr, strlen(ipAddr));

	if (m_type == TCP_CONN)
	{
		if (ipAddr == NULL)
		{
			//本机作为服务端
			m_pTCP->TCPConAsSer(port);
		}
		else
		{
			//本机作为客户端
			m_pTCP->TCPConAsCli(port, ipAddr);
		}
	}
	else if (m_type == UDP_CONN)
	{
		if (ipAddr == NULL)
		{
			//本机作为服务端（光电、伺服）
			m_pUDP->UDPConAsSer(port);
		}
		else
		{
			//本机作为客户端（干扰机）
			m_pUDP->UDPConAsCli(port, ipAddr);
		}
	}
}

void NetConnThread::setConnState(int state)
{
	m_connCtrl = state;

	if (m_type == UDP_CONN)
	{
		if (m_connCtrl == 0)
		{
			if (m_ipStr[0] == 0)
			{
				m_pUDP->CloseSocket();
			}
		}
		else
		{
			if (m_ipStr[0] == 0)
			{
				m_pUDP->UDPConAsSer(m_port);
			}
		}
	}
}

void NetConnThread::run()
{
	static char bufRecv[10240] = { 0 };
	char *tempBuf = NULL;
	int recvBufLen = 0;

	while (!stopped)
	{
		if (m_connCtrl == 0)
		{
			msleep(100);
			continue;
		}

		if (m_type == TCP_CONN)
		{
			if (m_connectState != m_pTCP->GetConState())
			{
				m_connectState = m_pTCP->GetConState();
				emit sigStateChange(m_connectState);
			}
			recvBufLen = m_pTCP->RecvData();
			if (recvBufLen > 0)
			{
				m_pTCP->GetRecvBuf(bufRecv);
			}
		}
		else if (m_type == UDP_CONN)
		{
			if (m_connectState == 1)
			{
				if ((m_qDateTime.offsetFromUtc() - m_dateTime) > 3)
				{
					m_connectState = -1;
					emit sigStateChange(m_connectState);
				}
			}
			recvBufLen = m_pUDP->RecvData();
			if (recvBufLen > 0)
			{
				m_pUDP->GetRecvBuf(bufRecv);
			}
		}
		if (recvBufLen > 0)
		{
			//为防止网络消息空间被重叠使用，使用临时创建的控件保存数据，接收方收到后进行销毁
			tempBuf = (char*)malloc(recvBufLen);
			memset(tempBuf, 0, recvBufLen);
			memcpy(tempBuf, bufRecv, recvBufLen);
			emit sigSendData(tempBuf, recvBufLen);

			if (m_type == UDP_CONN)
			{
				if (m_connectState == -1)
				{
					m_dateTime = m_qDateTime.offsetFromUtc();
					m_connectState = 1;
					emit sigStateChange(m_connectState);
				}
			}
		}

		if (m_isSpecial == 0)
		{
			msleep(1);
		}
		else
		{
			//usleep(10);
		}
	}
}

void NetConnThread::stop()
{
	stopped = true;
}

void NetConnThread::slotDataReceived(char *data, int len)
{
	if (data == NULL || len <= 0)
		return;

	if (m_type == TCP_CONN)
	{
		m_pTCP->SetSendBuf(data, len);
		m_pTCP->SendData();
	}
	else
	{
		if (m_connCtrl == 0)
		{
			return;
		}

		m_pUDP->SetSendBuf(data, len);
		m_pUDP->SendData();
	}
}