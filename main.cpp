#include "mainwindow.h"
//#include "mpCK.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QLabel>
#include <QMovie>
#include <QDesktopWidget>
#include "opengl.h"
int main(int argc, char *argv[])
{
	
	//��ֹ�����¼�������¼�����
	QApplication a(argc, argv);
	
	//�����䶼û�ã�����
	//a.setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents, false);
	//a.setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents, false);

	MainWindow w;

	QDesktopWidget *desktop = QApplication::desktop();

	w.setGeometry(0, 0, 3840, 1080);
	//w.setGeometry(desktop->screenGeometry(1));
	//w.setGeometry(0, 0, 960, 1080);
	//w.setGeometry(0, 0, 2736, 1824);
	//w.setWindowFlags(Qt::FramelessWindowHint);
	//w.setWindowState(Qt::WindowFullScreen);

	//w.setWindowFlags(Qt::WindowStaysOnTopHint);

	w.show();
		
	OpenGL nativeEventFilterZ=new OpenGL(0);
	a.installNativeEventFilter(&nativeEventFilterZ);

	

	return a.exec();
}
