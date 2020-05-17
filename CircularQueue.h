#pragma once

//数据缓冲池最大长度
#define MAX_IRCULAT_QUEUE_SIZE (100 * 1024 * 1024)

class CircularQueue
{
public:
	CircularQueue();
	~CircularQueue();

	int FillData(char *tempBuf, int len);
	int GetData(char *data, int len);
	int SeeFlag(char *data, int len);
	int Length();
	int Clear();
private:
	//
	char m_buf[MAX_IRCULAT_QUEUE_SIZE];
	int m_bufSize;
	int m_validLen;
	int m_readIndex;
	int m_writeIndex;
};

