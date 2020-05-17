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

		BaseCheck();	//实时性检查
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
	//实时性检查（功能待研究）

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

//语音
void MorphologyInput::onRecvSpeechResult(char *text, int len)
{
	//采用映射表
}

//按键
void MorphologyInput::onRecvKeyMsg(int keyId)
{
	//映射表结构如何设计？
	//暂时使用switch...case...进行映射判断
	switch (keyId)
	{
		
	case 1:
	case 2:
	case 3:
		//表示选择

		break;
	case 4:
	case 5:
		//表示文本

		break;
	case 6:
	case 7:
		//表示其他

		break;
	}
}

//触控
void MorphologyInput::onRecvTouchMsg()		
{
	//触控消息的映射关系如何？
}

//眼动
void MorphologyInput::onRecvSightMsg()
{
	//暂不考虑
}

//手势
void MorphologyInput::onRecvGestureMsg()
{
	//暂不考虑
}