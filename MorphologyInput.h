#ifndef MORPHOLOGYINPUT_H
#define MORPHOLOGYINPUT_H

/*
���ƣ���ͨ������-�ʷ��㴦��
���ã�������Ķ�ͨ���źŽ��й�һ������
�ѵ㣺���������ʽ��ι�һ��
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

	//��һ����ʽ�Ĵʷ������Ϣ����
	QList<Primitive*> m_list;

	//
	void DestroyAll();

	//
	int BaseCheck();
	
public slots:
	void onRecvSpeechResult(char *text, int len);	//����
	void onRecvKeyMsg(int keyId);					//����
	void onRecvTouchMsg();							//����
	void onRecvSightMsg();							//�۶�
	void onRecvGestureMsg();						//����

signals:
	void sigPrimitive(Primitive *pri);
};

#endif // GRAMMARINPUT_H
