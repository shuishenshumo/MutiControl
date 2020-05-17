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

	//Ĭ�ϵ�ǰֻ��һ�ֲ���ģʽ
	SelectLayout(0);
}

LayoutWindow::~LayoutWindow()
{
	//��Ҫ�ͷſռ䣬���ﻹû���ü�д


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

		//�����ǰ����ִ�ж�������ֹͣǰһ�������Ķ�ʱ��
		if (m_isChanging == 1)
		{
			m_isChanging = 0;
			killTimer(m_nTimerDrawId);
		}

		//���´�����ʱ��
		m_isChanging = 1;
		m_nTimerDrawId = startTimer(100);
	}
}

void LayoutWindow::onShowWindow(int type)
{
	int tempWidth = 0;

	//������ѡģʽ������Ŀ�겼�ֲ���
	switch(type)
	{
	case 0:
		m_nParaTarget = 0;
		break;
	default:
		break;
	}

	//�����ǰ����ִ�ж�������ֹͣǰһ�������Ķ�ʱ��
	if(m_isChanging == 1)
	{
		m_isChanging = 0;
		killTimer(m_nTimerDrawId);
	}

	//���´�����ʱ��
	m_isChanging = 1;
	m_nTimerDrawId = startTimer(100);
}


//�������Ŀǰ֧�ִ������
void LayoutWindow::SelectLayout(int type)
{
	QStackedWidget *qsw = NULL;
	int num = -1;
	int needNum = 0;
	int listLen = 0;

	//�����������
	ClearWidget();

	//������Ʋ���
	switch(type)
	{
	case 0:
		//Ĭ�ϲ���
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

		//���ò���λ��
		ui.gridLayout->addWidget(m_stackedWidgetList.at(0), 0, 0);
		//ui.gridLayout->addWidget(m_stackedWidgetList.at(1), 0, 1);
		//ui.gridLayout->addWidget(m_stackedWidgetList.at(2), 0, 2);

		//���ò��ֱ���
		//ui.gridLayout->setColumnStretch(0, m_a1);
		//ui.gridLayout->setColumnStretch(1, m_a2);
		//ui.gridLayout->setColumnStretch(2, m_a3);

		//������ʾ����
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
	//���GridLayout�е��Ӳ��ֹ�����
	QLayoutItem *child;
	while(child = ui.gridLayout->takeAt(0))
		delete child;

	//���m_stackedWidgetList�б���ɾ������StackedWidget
	while(!m_stackedWidgetList.isEmpty())
	{
		//ȡ��һ��stackWidget
		QStackedWidget *sw = NULL;
		sw = m_stackedWidgetList.at(0);

		//����ǰstackedWidget�е�UI���ú����Զ�ʹ���е�UI����hide()
		sw->removeWidget(sw->widget(0));

		//����ǰstackedWidget��list���Ƴ�
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
		//���㵱ǰ�������ܴﵽ�Ĳ��ֲ���
		//���ݵ����������õ�ǰ���ֲ���
		if(abs(m_nPara - m_nParaTarget) <= m_speed )
		{
			//һ����λ
			m_nPara = m_nParaTarget;
			result = 1;
		}else
		{
			//�ֲ����У��ȴ��´μ�������
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

		//���㲢���ò��ֱ���
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
			//������Ϻ��Զ��رն�ʱ��
			m_isChanging = 0;
			killTimer(m_nTimerDrawId);
		}
	}
}