#ifndef QTITLE_H
#define QTITLE_H

#include <QWidget>
#include "ui_qtitle.h"
#include <qtimer.h>
#include <qstring.h>

class QTitle : public QWidget
{
	Q_OBJECT

public:
	QTitle(QWidget *parent = 0);
	~QTitle();

	QTimer *m_pTimer;

	void SetLatLng(float lat, float lng);
	void SetTitle(QString str);

public slots:
	void onUpdate();

private:
	Ui::QTitle ui;
};

#endif // QTITLE_H
