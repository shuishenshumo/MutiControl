#include "mainwindow.h"
#include "GlobalObject.h"
#include "asr_record_sample.h"
#include "LibHOTAS.h"

#include <QString>
#include <QTextCodec>
#include <qdebug.h>
#include <QKeyEvent>
#include <QLibrary>
#include <QUrl>
#include <qstring.h>
#include <QStringList>
#include <QWindow>
#include "opengl.h"
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

//显控窗口【重要】
OpenGL *g_openGL = NULL;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//然后生成窗口类
	g_openGL = new OpenGL(this);
	g_openGL->hide();
	
	//创建布局类
	m_layoutId = 0;
	m_wLayout = new LayoutWindow(this);
	ui.stackedWidget->addWidget(m_wLayout);
	ui.stackedWidget->setCurrentIndex(m_layoutId);
}

MainWindow::~MainWindow()
{
	if (g_openGL != NULL)
	{
		delete g_openGL;
	}
	if (m_wLayout != NULL)
	{
		delete m_wLayout;
	}
	
}


bool MainWindow::eventFilter(QObject *obj, QEvent *ev)
{
	return QObject::eventFilter(obj, ev);
}

void MainWindow::setQSS(QWidget * father, QString qssContent)
{
	if (father == NULL)
	{
		return;
	}
	//qDebug()<<"set qss "<<qssContent;
	father->setStyleSheet(qssContent);
	QObjectList mObjs = father->children();
	for (int i = 0; i < mObjs.count(); ++i)
	{
		QWidget *son = dynamic_cast<QWidget *>(mObjs.at(i));
		setQSS(son, qssContent);
	}
}
/*void  MainWindow::getDLL(VAPS *m_p)
{
	//m_vapsList2 = m_p;
}*/

void MainWindow::initQSS(QWidget * qWidget)
{
	if (QFile::exists(QCoreApplication::applicationDirPath() + "/owlConfig/owl_qss_1.qss"))
	{
		qDebug() << "read qss file right";
		QString path = QCoreApplication::applicationDirPath() + "/owlConfig/owl_qss_1.qss";
		QString	styleSheet = "";
		QFile fileStyleSheet(path);
		if (fileStyleSheet.open(QFile::ReadOnly))
		{
			styleSheet = QString::fromLocal8Bit(fileStyleSheet.readAll());
			setQSS(qWidget, styleSheet);
		}
	}
	else
	{
		qDebug() << "read qss file error";
		return;
	}
}