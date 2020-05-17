#ifndef TEXTTOSPEECH_H
#define TEXTTOSPEECH_H

#pragma execution_character_set("UTF-8")

#define MaxBufferSize 5//ͬʱ�ڶ����л���ĸ澯�������������������ʱ����ն��У����澯����̫��澯��

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QQueue>
#include <ActiveQt/QAxObject>
#include <ActiveQt/QAxBase>
#include <oaidl.h>
#include <windows.h>
#include "sapi.h"
#include "sphelper.h"
#pragma comment(lib, "sapi.lib")

class TextToSpeech : public QThread
{
	Q_OBJECT

private:
	void run();
private:
	bool isStop;
	QMutex qMutex;
public:
	TextToSpeech();
	~TextToSpeech();

	static TextToSpeech *GetInstance()
	{
		static TextToSpeech textToSpeech;

		return &textToSpeech;
	}
	ISpVoice  *pSpVoice;
	QQueue<QString> textToSpeakQueue;
	mutable QAxObject m_voice;
	QString EnglishVoiceKey;
	QString ChineseVoiceKey;
	QString clsidSpObjectToken;
	QString clsidSpVoice;	
	long voiceRate;
	long voiceVolume;
	void speakText(QString);
	void setRate(long);//-10~10
	long getRate(); 
	void setVolume(long);//0-100
	long getVolume();
	void resumeSpeak();//�����ʶ�
	void pauseSpeak();//��ͣ�ʶ�
	void stopThread();
	void startThread();
};

#endif // TEXTTOSPEECH_H
