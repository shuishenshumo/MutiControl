#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <qobject.h>
#include <QtWidgets/QMainWindow>
#include <QVector3D>
#include <windows.h>
#include <qstring.h>
#include <QTextCodec>
#include <QLayOut>
#include <QProcess>
#include <qabstractnativeeventfilter.h>
#include "ui_mainwindow.h"
#include "layoutwindow.h"
#include "SRComThread.h"
#include "TextToSpeech.h"
#include <QDebug>

#include <iostream>
using namespace std;
#pragma comment(lib, "user32.lib")


struct UartCmdData
{
	 char Head;//0xF5
	char Cmd;
	char OddCheck;
	char Tail;//0x5F
	char FlagR;
	char FlagN;
};

class MainWindow : public QMainWindow
{
	Q_OBJECT


public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	
public slots:
//void getDLL(VAPS *m_p);



protected:
	bool eventFilter(QObject *obj, QEvent *ev);//本Ui的事件过滤器

private:
	Ui::MainWindowClass ui;

	//页面布局管理
	int m_layoutId;
	LayoutWindow *m_wLayout;
	int m_nCurPageIndex;
	int m_nNumberOfPages;

	//HOTAS
	HWND m_hWnd;
	int m_iX;
	int m_iY;
	bool m_hasHotas;

	//QSS
	void initQSS(QWidget *);
	void setQSS(QWidget * father, QString qssContent);
	


};

#endif // MAINWINDOW_H
