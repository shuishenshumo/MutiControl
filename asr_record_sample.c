/*
* ������д(iFly Auto Transform)�����ܹ�ʵʱ�ؽ�����ת���ɶ�Ӧ�����֡�
*/

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <errno.h>
#include <process.h>

#include "../include/qisr.h"
#include "../include/msp_cmn.h"
#include "../include/msp_errors.h"
#include "./include/speech_recognizer.h"

#define FRAME_LEN	640 
#define	BUFFER_SIZE	4096

enum{
	EVT_START = 0,
	EVT_STOP,
	EVT_QUIT,
	EVT_TOTAL
};
static HANDLE events[EVT_TOTAL] = {NULL,NULL,NULL};

static COORD begin_pos = {0, 0};
static COORD last_pos = {0, 0};
#define SAMPLE_RATE_16K     (16000)
#define SAMPLE_RATE_8K      (8000)
#define MAX_GRAMMARID_LEN   (32)
#define MAX_PARAMS_LEN      (1024)

const char * ASR_RES_PATH        = "fo|res/asr/common.jet";  //�����﷨ʶ����Դ·��
//const char * ASR_RES_PATH        = "msc/res/asr/common.jet";  //�����﷨ʶ����Դ·��
#ifdef _WIN64
const char * GRM_BUILD_PATH      = "res/asr/GrmBuilld_x64";  //���������﷨ʶ�������������ݱ���·��
#else
const char * GRM_BUILD_PATH      = "res/asr/GrmBuilld";  //���������﷨ʶ�������������ݱ���·��
//const char * GRM_BUILD_PATH = "msc/res/asr/GrmBuilld";  //���������﷨ʶ�������������ݱ���·��
#endif
const char * GRM_FILE            = "call.bnf"; //��������ʶ���﷨�������õ��﷨�ļ�
const char * LEX_NAME            = "contact"; //��������ʶ���﷨��contact�ۣ��﷨�ļ�Ϊ��ʾ����ʹ�õ�call.bnf��
typedef struct _UserData {
	int     build_fini;  //��ʶ�﷨�����Ƿ����
	int     update_fini; //��ʶ���´ʵ��Ƿ����
	int     errcode; //��¼�﷨��������´ʵ�ص�������
	char    grammar_id[MAX_GRAMMARID_LEN]; //�����﷨�������ص��﷨ID
}UserData;

int build_grammar(UserData *udata); //��������ʶ���﷨����
int update_lexicon(UserData *udata); //��������ʶ���﷨�ʵ�
int run_asr(UserData *udata); //���������﷨ʶ��

int build_grm_cb(int ecode, const char *info, void *udata)
{
	UserData *grm_data = (UserData *)udata;

	if (NULL != grm_data) {
		grm_data->build_fini = 1;
		grm_data->errcode = ecode;
	}

	if (MSP_SUCCESS == ecode && NULL != info) {
		printf("�����﷨�ɹ��� �﷨ID:%s\n", info);
		if (NULL != grm_data)
			_snprintf(grm_data->grammar_id, MAX_GRAMMARID_LEN - 1, info);
	}
	else
		printf("�����﷨ʧ�ܣ�%d\n", ecode);

	return 0;
}

int build_grammar(UserData *udata)
{
	FILE *grm_file                           = NULL;
	char *grm_content                        = NULL;
	unsigned int grm_cnt_len                 = 0;
	char grm_build_params[MAX_PARAMS_LEN]    = {NULL};
	int ret                                  = 0;

	grm_file = fopen(GRM_FILE, "rb");	
	if(NULL == grm_file) {
		printf("��\"%s\"�ļ�ʧ�ܣ�[%s]\n", GRM_FILE, strerror(errno));
		return -1; 
	}

	fseek(grm_file, 0, SEEK_END);
	grm_cnt_len = ftell(grm_file);
	fseek(grm_file, 0, SEEK_SET);

	grm_content = (char *)malloc(grm_cnt_len + 1);
	if (NULL == grm_content)
	{
		printf("�ڴ����ʧ��!\n");
		fclose(grm_file);
		grm_file = NULL;
		return -1;
	}
	fread((void*)grm_content, 1, grm_cnt_len, grm_file);
	grm_content[grm_cnt_len] = '\0';
	fclose(grm_file);
	grm_file = NULL;

	_snprintf(grm_build_params, MAX_PARAMS_LEN - 1, 
		"engine_type = local, \
		asr_res_path = %s, sample_rate = %d, \
		grm_build_path = %s, ",
		ASR_RES_PATH,
		SAMPLE_RATE_16K,
		GRM_BUILD_PATH
		);
	ret = QISRBuildGrammar("bnf", grm_content, grm_cnt_len, grm_build_params, build_grm_cb, udata);

	free(grm_content);
	grm_content = NULL;

	return ret;
}

int update_lex_cb(int ecode, const char *info, void *udata)
{
	UserData *lex_data = (UserData *)udata;

	if (NULL != lex_data) {
		lex_data->update_fini = 1;
		lex_data->errcode = ecode;
	}

	if (MSP_SUCCESS == ecode)
		printf("���´ʵ�ɹ���\n");
	else
		printf("���´ʵ�ʧ�ܣ�%d\n", ecode);

	return 0;
}

int update_lexicon(UserData *udata)
{
	const char *lex_content                   = "��ΰ\n������";
	unsigned int lex_cnt_len                  = strlen(lex_content);
	char update_lex_params[MAX_PARAMS_LEN]    = {NULL}; 

	_snprintf(update_lex_params, MAX_PARAMS_LEN - 1, 
		"engine_type = local, text_encoding = GB2312, \
		asr_res_path = %s, sample_rate = %d, \
		grm_build_path = %s, grammar_list = %s, ",
		ASR_RES_PATH,
		SAMPLE_RATE_16K,
		GRM_BUILD_PATH,
		udata->grammar_id);
	return QISRUpdateLexicon(LEX_NAME, lex_content, lex_cnt_len, update_lex_params, update_lex_cb, udata);
}
static void show_result(char *string, char is_over)
{
	COORD orig, current;
	CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE w = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(w, &info);
	current = info.dwCursorPosition;

	if(current.X == last_pos.X && current.Y == last_pos.Y ) {
		SetConsoleCursorPosition(w, begin_pos);
	} else {
		/* changed by other routines, use the new pos as start */
		begin_pos = current;
	}
	if(is_over)
		SetConsoleTextAttribute(w, FOREGROUND_GREEN);
	printf("Result: [ %s ]\n", string);
	if(is_over)
		SetConsoleTextAttribute(w, info.wAttributes);

	GetConsoleScreenBufferInfo(w, &info);
	last_pos = info.dwCursorPosition;
}

char *g_result = NULL;
volatile unsigned int g_buffersize = BUFFER_SIZE;
volatile int g_flagResult = 0;
void on_result(const char *result, char is_last)
{
	//FILE *fp;
	if (result) {
		size_t left = g_buffersize - 1 - strlen(g_result);
		size_t size = strlen(result);
		if (left < size) {
			g_result = (char*)realloc(g_result, g_buffersize + BUFFER_SIZE);
			if (g_result)
				g_buffersize += BUFFER_SIZE;
			else {
				printf("mem alloc failed\n");
				return;
			}
		}
		strncat(g_result, result, size);
		//show_result(g_result, is_last);

		g_flagResult = 1;
	}
}

void on_speech_begin()
{
	if (g_result)
	{
		free(g_result);
	}
	g_result = (char*)malloc(BUFFER_SIZE);
	g_buffersize = BUFFER_SIZE;
	memset(g_result, 0, g_buffersize);

	printf("Start Listening...\n");
}

void on_speech_end(int reason)
{
	if (reason == END_REASON_VAD_DETECT)
		printf("\nSpeaking done \n");
	else
		printf("\nRecognizer error %d\n", reason);
}

int start_sr()
{
	SetEvent(events[EVT_START]);
	return 0;
}

int stop_sr()
{
	SetEvent(events[EVT_STOP]);
	return 0;
}

int quit_sr()
{
	SetEvent(events[EVT_QUIT]);
	return 0;
}

/* demo recognize the audio from microphone */
static void demo_mic(const char* session_begin_params)
{
	int errcode;
	int i = 0;
	HANDLE helper_thread = NULL;

	struct speech_rec asr;
	DWORD waitres;
	char isquit = 0;

	struct speech_rec_notifier recnotifier = {
		on_result,
		on_speech_begin,
		on_speech_end
	};

	errcode = sr_init(&asr, session_begin_params, SR_MIC, DEFAULT_INPUT_DEVID, &recnotifier);
	if (errcode) {
		printf("speech recognizer init failed\n");
		return;
	}

	for (i = 0; i < EVT_TOTAL; ++i) {
		events[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
	}

 	while (1) {
		waitres = WaitForMultipleObjects(EVT_TOTAL, events, FALSE, INFINITE);
		switch (waitres) {
		case WAIT_FAILED:
		case WAIT_TIMEOUT:
			printf("Why it happened !?\n");
			break;
		case WAIT_OBJECT_0 + EVT_START:
			if (errcode = sr_start_listening(&asr)) {
				printf("start listen failed %d\n", errcode);
				isquit = 1;
			}
			break;
		case WAIT_OBJECT_0 + EVT_STOP:		
			if (errcode = sr_stop_listening(&asr)) {
				printf("stop listening failed %d\n", errcode);
				isquit = 1;
			}
			break;
		case WAIT_OBJECT_0 + EVT_QUIT:
			sr_stop_listening(&asr);
			isquit = 1;
			break;
		default:
			break;
		}
		if (isquit)
			break;
	}

	for (i = 0; i < EVT_TOTAL; ++i) {
		if (events[i])
			CloseHandle(events[i]);
	}

	sr_uninit(&asr);
}

int run_asr(UserData *udata)
{
	char asr_params[MAX_PARAMS_LEN]    = {NULL};
	const char *rec_rslt               = NULL;
	const char *session_id             = NULL;
	const char *asr_audiof             = NULL;
	FILE *f_pcm                        = NULL;
	char *pcm_data                     = NULL;
	long pcm_count                     = 0;
	long pcm_size                      = 0;
	int last_audio                     = 0;
	int aud_stat                       = MSP_AUDIO_SAMPLE_CONTINUE;
	int ep_status                      = MSP_EP_LOOKING_FOR_SPEECH;
	int rec_status                     = MSP_REC_STATUS_INCOMPLETE;
	int rss_status                     = MSP_REC_STATUS_INCOMPLETE;
	int errcode                        = -1;
	int aud_src                        = 0;


	//�����﷨ʶ���������
	_snprintf(asr_params, MAX_PARAMS_LEN - 1, 
		"engine_type = local, \
		asr_res_path = %s, sample_rate = %d, \
		grm_build_path = %s, local_grammar = %s, \
		result_type = result, result_encoding = GB2312, ",
		ASR_RES_PATH,
		SAMPLE_RATE_16K,
		GRM_BUILD_PATH,
		udata->grammar_id
		);

	//ֱ��ʹ����������ʶ��ʽ
	demo_mic(asr_params);


	return 0;
}

/* main thread: start/stop record ; query the result of recgonization.
 * record thread: record callback(data write)
 * helper thread: ui(keystroke detection)
 */
unsigned int  __stdcall sr_main(void * para)
{
	const char *login_config    = "appid = 5a0cc623"; //��¼����
	UserData asr_data; 
	int ret                    = 0 ;

	ret = MSPLogin(NULL, NULL, login_config); //��һ������Ϊ�û������ڶ�������Ϊ���룬��NULL���ɣ������������ǵ�¼����
	if (MSP_SUCCESS != ret) {
		printf("��¼ʧ�ܣ�%d\n", ret);
		goto exit;
	}

	memset(&asr_data, 0, sizeof(UserData));
	printf("��������ʶ���﷨����...\n");
	ret = build_grammar(&asr_data);  //��һ��ʹ��ĳ�﷨����ʶ����Ҫ�ȹ����﷨���磬��ȡ�﷨ID��֮��ʹ�ô��﷨����ʶ�������ٴι���
	if (MSP_SUCCESS != ret) {
		printf("�����﷨����ʧ�ܣ�\n");
		goto exit;
	}
	while (1 != asr_data.build_fini)
		_sleep(300);
	if (MSP_SUCCESS != asr_data.errcode)
		goto exit;
	printf("����ʶ���﷨���繹����ɣ���ʼʶ��...\n");
	ret = run_asr(&asr_data);
	if (MSP_SUCCESS != ret) {
		printf("�����﷨ʶ�����: %d \n", ret);
		goto exit;
	}

	printf("�밴���������\n");
	_getch();
	printf("���������﷨�ʵ�...\n");
	ret = update_lexicon(&asr_data);  //���﷨�ʵ���еĴ�����Ҫ����ʱ������QISRUpdateLexicon�ӿ���ɸ���
	if (MSP_SUCCESS != ret) {
		printf("���´ʵ����ʧ�ܣ�\n");
		goto exit;
	}
	while (1 != asr_data.update_fini)
		_sleep(300);
	if (MSP_SUCCESS != asr_data.errcode)
		goto exit;
	printf("���������﷨�ʵ���ɣ���ʼʶ��...\n");
	ret = run_asr(&asr_data);
	if (MSP_SUCCESS != ret) {
		printf("�����﷨ʶ�����: %d \n", ret);
		goto exit;
	}

exit:
	MSPLogout();
	printf("�밴������˳�...\n");
	_getch();
	return 0;
}
