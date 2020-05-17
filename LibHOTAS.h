#ifndef _LIBHOTAS_H_
#define _LIBHOTAS_H_

/* callback fxn */
typedef void(*Callback_HOTASMove)(int iX, int iY);
typedef void(*Callback_HOTASButtonDown)();
typedef void(*Callback_HOTASButtonUp)();

/* dll export fxn */
typedef int(*HOTAS_Init)(HWND hWnd,Callback_HOTASMove fxnHOTASMove,Callback_HOTASButtonDown fxnHOTASButtonDown,Callback_HOTASButtonUp fxnHOTASButtonUp);
typedef int(*HOTAS_ActiveMsg)(MSG* pMsg);
typedef int(*HOTAS_Uint)();

HINSTANCE hHOTASDll=0;

HOTAS_Init			HOTAS_fxnInit;
HOTAS_ActiveMsg		HOTAS_fxnActiveMsg;
HOTAS_Uint			HOTAS_fxnUint;

/* err list */
#define err_HOTAS_NO_HWND -101
#define err_HOTAS_NO_CALLBACK_MOVE -102
#define err_HOTAS_NO_CALLBACK_BUTTONDOWN -103
#define err_HOTAS_NO_CALLBACK_BUTTONUP -104

#define err_HOTAS_NO_DEVICE -111
#define err_HOTAS_TOOMANY_DEVICE -112
#define err_HOTAS_DEVICE_INIT -113

#endif