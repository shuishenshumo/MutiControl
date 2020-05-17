#include "MorphologyInput.h"

MorphologyInput::MorphologyInput(QObject *parent)
	: QThread(parent)
{
	stopped = false;
}

MorphologyInput::~MorphologyInput()
{
	DestroyAll();
}

Primitive* MorphologyInput::PushPrimitive(PRI_TYPE type, void* para)
{
	Primitive* pri = new Primitive;
	if (pri != NULL)
	{
		pri->type = type;
		pri->para = para;
		m_list.append(pri);

		BaseCheck();	//ʵʱ�Լ��
	}
	return pri;
}

Primitive* MorphologyInput::PopPrimitive()
{
	Primitive* pri = NULL;
	if (m_list.isEmpty() == false)
	{
		pri = m_list.at(0);
		m_list.pop_front();
	}
	return pri;
}

void MorphologyInput::DestroyAll()
{
	Primitive* pri = NULL;
	while (m_list.isEmpty() == false)
	{
		pri = m_list.at(0);
		m_list.pop_front();
		if (pri != NULL)
		{
			if (pri->para != NULL)
			{
				delete pri->para;
			}
			delete pri;
		}
	}
}

int MorphologyInput::BaseCheck()
{
	//ʵʱ�Լ�飨���ܴ��о���

	return 0;
}

void MorphologyInput::run()
{
	Primitive* pri = NULL;
	while (!stopped)
	{
		msleep(10);
		while (m_list.isEmpty() == false)
		{
			pri = PopPrimitive();
			emit sigPrimitive(pri);
		}
	}
}

void MorphologyInput::stop()
{
	stopped = true;
}

//����
void MorphologyInput::onRecvSpeechResult(char *text, int len)
{
	//����ӳ���
}

//����
void MorphologyInput::onRecvKeyMsg(int keyId)
{
	//ӳ���ṹ�����ƣ�
	//��ʱʹ��switch...case...����ӳ���ж�
	switch (keyId)
	{
		
	case 1:
	case 2:
	case 3:
		//��ʾѡ��

		break;
	case 4:
	case 5:
		//��ʾ�ı�

		break;
	case 6:
	case 7:
		//��ʾ����

		break;
	}
}

//����
void MorphologyInput::onRecvTouchMsg()		
{
	//������Ϣ��ӳ���ϵ��Σ�
}

//�۶�
void MorphologyInput::onRecvSightMsg()
{
	//�ݲ�����
}

//����
void MorphologyInput::onRecvGestureMsg()
{
	//�ݲ�����
}