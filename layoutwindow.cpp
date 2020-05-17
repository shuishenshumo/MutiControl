#include "layoutwindow.h"
#include "GlobalObject.h"

LayoutWindow::LayoutWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//
	m_nPara = 0;
	m_nParaTarget = 0;
	m_isChanging = 0;
	m_nTimerDrawId = 0;
	m_speed = 16;

	//
	for(int i = 0; i < 5; i++)
	{
		m_stackedWidgetListLeft.append(new QStackedWidget(this));
		m_stackedWidgetListLeft.last()->hide();
	}

	//默认当前只有一种布局模式
	SelectLayout(0);
}

LayoutWindow::~LayoutWindow()
{
	//需要释放空间，这里还没来得及写


}

void LayoutWindow::resizeEvent(QResizeEvent* size)
{
	int tempWidth = 0;
	if (m_nParaTarget != 0)
	{
		//tempWidth = g_actionWindow->ui.groupBox_Background->width();
		tempWidth = 0;
		if (tempWidth < this->width())
		{
			m_nParaTarget = (int)(100.0 * tempWidth / this->width());
		}
		else
		{
			m_nParaTarget = 50;
		}

		//如果当前正在执行动作，则停止前一个动作的定时器
		if (m_isChanging == 1)
		{
			m_isChanging = 0;
			killTimer(m_nTimerDrawId);
		}

		//重新创建定时器
		m_isChanging = 1;
		m_nTimerDrawId = startTimer(100);
	}
}

void LayoutWindow::onShowWindow(int type)
{
	int tempWidth = 0;

	//根据所选模式，设置目标布局参数
	switch(type)
	{
	case 0:
		m_nParaTarget = 0;
		break;
	default:
		break;
	}

	//如果当前正在执行动作，则停止前一个动作的定时器
	if(m_isChanging == 1)
	{
		m_isChanging = 0;
		killTimer(m_nTimerDrawId);
	}

	//重新创建定时器
	m_isChanging = 1;
	m_nTimerDrawId = startTimer(100);
}


//布局设计目前支持代码设计
void LayoutWindow::SelectLayout(int type)
{
	QStackedWidget *qsw = NULL;
	int num = -1;
	int needNum = 0;
	int listLen = 0;

	//清空现有内容
	ClearWidget();

	//重新设计布局
	switch(type)
	{
	case 0:
		//默认布局
		m_a1 = 0;
		m_a2 = 0;
		m_a3 = 100;

		//
		needNum = 1;

		//
		listLen = m_stackedWidgetListLeft.length();
		if(listLen < needNum)
		{
			for(int i = 0; i < needNum - listLen; i++)
			{
				m_stackedWidgetListLeft.append(new QStackedWidget(this));
				m_stackedWidgetListLeft.last()->hide();
			}
		}
		//
		for(int i = 0; i < needNum; i++)
		{
			m_stackedWidgetList.append(m_stackedWidgetListLeft.takeFirst());
			m_stackedWidgetList.last()->show();
		}

		//设置布局位置
		ui.gridLayout->addWidget(m_stackedWidgetList.at(0), 0, 0);
		//ui.gridLayout->addWidget(m_stackedWidgetList.at(1), 0, 1);
		//ui.gridLayout->addWidget(m_stackedWidgetList.at(2), 0, 2);

		//设置布局比例
		//ui.gridLayout->setColumnStretch(0, m_a1);
		//ui.gridLayout->setColumnStretch(1, m_a2);
		//ui.gridLayout->setColumnStretch(2, m_a3);

		//设置显示画面
		m_stackedWidgetList.at(0)->addWidget(g_openGL);
		m_stackedWidgetList.at(0)->setCurrentIndex(0);

		//m_stackedWidgetList.at(1)->addWidget(g_targetInfo);
		//m_stackedWidgetList.at(1)->setCurrentIndex(0);

		//m_stackedWidgetList.at(2)->addWidget(g_actionWindow);
		//m_stackedWidgetList.at(2)->setCurrentIndex(0);

		break;
	default:
		break;
	}
}

void LayoutWindow::ClearWidget()
{
	//清空GridLayout中的子布局管理类
	QLayoutItem *child;
	while(child = ui.gridLayout->takeAt(0))
		delete child;

	//清空m_stackedWidgetList列表，并删除所有StackedWidget
	while(!m_stackedWidgetList.isEmpty())
	{
		//取出一个stackWidget
		QStackedWidget *sw = NULL;
		sw = m_stackedWidgetList.at(0);

		//清理当前stackedWidget中的UI，该函数自动使其中的UI调用hide()
		sw->removeWidget(sw->widget(0));

		//将当前stackedWidget从list中移除
		m_stackedWidgetList.removeOne(sw);
		m_stackedWidgetListLeft.append(sw);
	}
}

//
int LayoutWindow::SetDynamicLayout(int type)
{
	int result = 0;
	if(type == 1)
	{
		//计算当前步骤所能达到的布局参数
		//根据弹出速率设置当前布局参数
		if(abs(m_nPara - m_nParaTarget) <= m_speed )
		{
			//一步到位
			m_nPara = m_nParaTarget;
			result = 1;
		}else
		{
			//分布进行，等待下次继续设置
			if(m_nPara > m_nParaTarget)
			{
				m_nPara = m_nPara - m_speed;
			}
			else if(m_nPara < m_nParaTarget)
			{
				m_nPara = m_nPara + m_speed;
			}
			result = 0;
		}

		//计算并设置布局比例
#if 0
		if(m_nPara <= 25)
		{
			m_a1 = m_nPara;
			m_a2 = 0;
			m_a3 = 100-m_nPara;
		}else if(m_nPara > 25 && m_nPara <= 50)
		{
			m_a1 = 25;
			m_a2 = m_nPara-25;
			m_a3 = 100-m_nPara;
		}
#else
		m_a1 = m_nPara;
		m_a2 = 0;
		m_a3 = 100 - m_nPara;
#endif
		ui.gridLayout->setColumnStretch(0, m_a1);
		ui.gridLayout->setColumnStretch(1, m_a2);
		ui.gridLayout->setColumnStretch(2, m_a3);
	}
	return result;
}

void LayoutWindow::timerEvent(QTimerEvent *e)
{
	int timeId = e->timerId();
	if(timeId == m_nTimerDrawId)
	{
		if(SetDynamicLayout(1))
		{
			//布局完毕后，自动关闭定时器
			m_isChanging = 0;
			killTimer(m_nTimerDrawId);
		}
	}
}