#ifndef QTARGETPOSINFO_H
#define QTARGETPOSINFO_H

#include <QWidget>
#include "ui_qtargetposinfo.h"

class QTargetPosInfo : public QWidget
{
	Q_OBJECT

public:
	QTargetPosInfo(QWidget *parent = 0);
	~QTargetPosInfo();

	void SetLatLng(float lat, float lng);

private:
	Ui::QTargetPosInfo ui;
};

#endif // QTARGETPOSINFO_H
