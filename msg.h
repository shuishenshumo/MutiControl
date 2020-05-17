#ifndef MSG_H
#define MSG_H

typedef enum file_transfer_e {
	FILE_TRANSFER_MODEL,
	FILE_TRANSFER_CMDS,
	FILE_TRANSFER_PCM,
	FILE_TRANSFER_NUM
} file_transfer_t;

typedef enum  netctrl_cmd_e {
	ASR_SESSION_REGISTER = 0,
	ASR_SESSION_UNREGISTER,
	ASR_KEEP_ALIVE,
	CAPTURE_START,
	CAPTURE_STOP,
	CAPTURE_FREQ_SWITCH,
	APP_STATUS_REPORT,
	ASR_PCM_SAVE,
	ASR_MODEL_SWITCH,
	ASR_CMDS_SWITCH,
	NETCTRL_CMD_NUM
} netctrl_cmd_t;

typedef enum netctrl_resp_e {
	ASR_SESSION_REGISTER_RESP,
	ASR_RESULT_SCORE_NOTIFY,
	ASR_RESULT_DATA_NOTIFY,
	ASR_SESSION_ALIVE_RESP,
	NETCTRL_RESP_NUM,
} netctrl_resp_t;

typedef struct reponse_head_s {
	unsigned int type;
	unsigned int session_id;
	unsigned int len;
} reponse_head_t;

typedef struct request_head_s {
	unsigned int type;
	unsigned int session_id;
	unsigned int len;
} request_head_t;

#endif // MSG_H
