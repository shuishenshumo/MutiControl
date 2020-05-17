#ifndef ASR_RECORD_SAMPLE_H
#define ASR_RECORD_SAMPLE_H

#include <stdlib.h>

extern "C"
{
unsigned int __stdcall sr_main(void * para);

int start_sr();
int stop_sr();
int quit_sr();

//±£´æ½á¹û
extern "C" char *g_result;
extern "C" volatile unsigned int g_buffersize;
extern "C" volatile int g_flagResult;
}

#endif
