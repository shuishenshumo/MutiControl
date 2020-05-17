#ifndef MORPHOLOGYINPUT_H
#define MORPHOLOGYINPUT_H

/*
名称：多通道控制-词法层处理
作用：将输入的多通道信号进行归一化处理
难点：多种输入格式如何归一化
*/

#include <QThread>
#include <qlist.h>
#include "Primitive.h"

#define MORPHOLOGY_TIME (1)

class MorphologyInput : public QThread
{
	Q_OBJECT

public:
	MorphologyInput(QObject *parent);
	~MorphologyInput();

	void stop();

	//
	Primitive* PushPrimitive(PRI_TYPE type, void* para);
	Primitive* PopPrimitive();

protected:
	void run();
private:
	volatile bool stopped;

	//归一化格式的词法输出消息缓冲
	QList<Primitive*> m_list;

	//
	void DestroyAll();

	//
	int BaseCheck();
	
public slots:
	void onRecvSpeechResult(char *text, int len);	//语音
	void onRecvKeyMsg(int keyId);					//按键
	void onRecvTouchMsg();							//触控
	void onRecvSightMsg();							//眼动
	void onRecvGestureMsg();						//手势

signals:
	void sigPrimitive(Primitive *pri);
};

#endif // GRAMMARINPUT_H
