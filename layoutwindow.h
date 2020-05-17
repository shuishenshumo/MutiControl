#ifndef LAYOUTWINDOW_H
#define LAYOUTWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QResizeEvent>
#include <qtimer.h>
#include "ui_layoutwindow.h"

class LayoutWindow : public QWidget
{
	Q_OBJECT

public:
	LayoutWindow(QWidget *parent = 0);
	~LayoutWindow();
	void resizeEvent(QResizeEvent* size);
private:
	Ui::LayoutWindow ui;
	
	QList<QStackedWidget*> m_stackedWidgetList;
	QList<QStackedWidget*> m_stackedWidgetListLeft;
	
	int m_nPara;
	int m_nParaTarget;
	int m_isChanging;
	int m_nTimerDrawId;
	int m_speed;
	int m_a1, m_a2, m_a3;
	void timerEvent(QTimerEvent *e);

	void ClearWidget();
	void SelectLayout(int type);
	int SetDynamicLayout(int type);
private slots:
	void onShowWindow(int type);
};

#endif // LAYOUTWINDOW_H
