#pragma once
#include "stdio.h"    
#include <thread>
#include <mutex> 
#include "Windows.h" 
//#include <mmeapi.h>
#pragma comment(lib, "winmm.lib")  
#define WAV_HEADER_LEN 44
#define MAX_RETRY_COUNT 50
#define BITS_PER_SAMPLE 16
#define CHANNLEL 1
using namespace std;
typedef void(*recordClosedCallBack)(void *);

#pragma pack(1)
typedef struct
{
	char riff[4];                 // "RIFF" ��־  
	int  totalLen;                // �ļ�����      
	char wave[4];                 // "WAVE" ��־  
	char fmt[4];                  // "fmt" ��־ 
	int  dwFMTLen;                // �����ֽڣ�������  һ��Ϊ16
	short fmtPcm;                 // ��ʽ���  
	short  channels;              // ������  
	int fmtSamplehz;              // ������ 
	int fmtBytepsec;              // λ��  
	short fmtBlockAlign;          // һ���������������ݿ��С  
	short fmtBitPerSample;        // һ������ռ�� bit ��  
	char data[4];                 // ���ݱ�Ƿ���data ��  
	int  dwDATALen;               // �������ݵĳ��ȣ����ļ�����С44һ��
}WaveHeader;

class RecordThread
{

private:
	std::mutex mut;
	int retryCount;
	recordClosedCallBack callBack;
	void * pCall;
	int nSamplesPerSec;
	volatile int isRun;
	volatile int isCancel;
	HWAVEIN hWaveIn;  //�����豸  
	WAVEFORMATEX waveform; //�ɼ���Ƶ�ĸ�ʽ���ṹ��   
	WAVEHDR wHdr[8]; //�ɼ���Ƶʱ�������ݻ���Ľṹ��
	char * recordBuffer;
	char * tempBuffer[8];
	int recordBufferSize;
	int tempBufferSize;
	int size;
	volatile int readSize;
	void recovery();
public:
	RecordThread();
	int start();
	void setCallBack(recordClosedCallBack cb, void * pCall);
	void cancel();
	void setSamplesPerSec(int samplesPerSec);
	int getSamplesPerSec();
	int read(char * pData, int size);
	void micCallBack2(HWAVEIN hwavein, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
	static void CALLBACK  micCallBack(HWAVEIN hwavein, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
	void addWaveHeader(char * filePath, int samplesPerSec);
	~RecordThread();
};

