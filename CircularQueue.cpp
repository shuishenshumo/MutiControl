#include "CircularQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

CircularQueue::CircularQueue()
{
	m_bufSize = MAX_IRCULAT_QUEUE_SIZE;
	m_validLen = 0;
	m_readIndex = 0;
	m_writeIndex = 0;
}

CircularQueue::~CircularQueue()
{

}

int CircularQueue::FillData(char *tempBuf, int len)
{
	int leftNum = m_bufSize - m_writeIndex;
	if (len <= leftNum)
	{
		//ֱ�ӷ�����
		memcpy(m_buf + m_writeIndex, tempBuf, len);
		m_writeIndex = (m_writeIndex + len) % m_bufSize;
		m_validLen += len;
	}
	else
	{
		//��Ҫ��ת
		memcpy(m_buf + m_writeIndex, tempBuf, leftNum);
		memcpy(m_buf, tempBuf + leftNum, len - leftNum);
		m_writeIndex = (len - leftNum) % m_bufSize;
		m_validLen += len;
	}

	return 0;
}

int CircularQueue::GetData(char *data, int len)
{
	int leftNum = m_bufSize - m_readIndex;

	if (m_validLen < len)
		return 0;

	if (len <= leftNum)
	{
		//ֱ�ӷ�����
		memcpy(data, m_buf + m_readIndex, len);
		m_readIndex = (m_readIndex + len) % m_bufSize;
		m_validLen -= len;
	}
	else
	{
		//��Ҫ��ת
		memcpy(data, m_buf + m_readIndex, leftNum);
		memcpy(data + leftNum, m_buf, len - leftNum);
		m_readIndex = (len - leftNum) % m_bufSize;
		m_validLen -= len;
	}

	return len;
}

int CircularQueue::Length()
{
	return m_validLen;
}

int CircularQueue::SeeFlag(char *data, int len)
{
	int leftNum = m_bufSize - m_readIndex;

	if (m_validLen < len)
		return 0;

	if (len <= leftNum)
	{
		//ֱ�ӷ�����
		memcpy(data, m_buf + m_readIndex, len);
	}
	else
	{
		//��Ҫ��ת
		memcpy(data, m_buf + m_readIndex, leftNum);
		memcpy(data + leftNum, m_buf, len - leftNum);
	}

	return len;
}

int CircularQueue::Clear()
{
	m_validLen = 0;
	m_readIndex = m_writeIndex;

	return 0;
}