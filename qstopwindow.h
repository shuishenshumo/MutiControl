#ifndef QSTOPWINDOW_H
#define QSTOPWINDOW_H

#include <QWidget>
#include "ui_qstopwindow.h"

class QStopWindow : public QWidget
{
	Q_OBJECT

public:
	QStopWindow(QWidget *parent = 0);
	~QStopWindow();

public slots:
	void onEdit();
	void onStop();

signals:
	void sigQStopWindowEdit();
	void sigQStopWindowStop();

private:
	Ui::QStopWindow ui;
};

#endif // QSTOPWINDOW_H
