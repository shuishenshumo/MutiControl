#ifndef QLWIDGET_H
#define QLWIDGET_H

#include <QWidget>
#include "ui_qlwidget.h"
class CtrlChannel;
class DataChannel;
namespace Ui {
	class QLWidget;
}


class QLWidget : public QWidget
{
	Q_OBJECT

public:
	QLWidget(QWidget *parent = 0);
	~QLWidget();

	public slots:
	void onStartButtonClicked();
	void onStopButtonClicked();
	void onRegisterButtonClicked();
	void onUnRegisterButtonClicked();
	void onSavePcmToggled(bool);
	void onScoreUpdate(QString);
	void onASRUpdate(QString);
	void onUpdateModelButtonClicked();
	void onUpdateCmdsButtonClicked();
	void onModelSwitchButtonClicked();
	void onCmdsSwitchButtonClicked();
	void onLoadButtonClicked();
	void onClientStateChanged(quint32, bool);
	void onModelUploadFinished(quint32);
	void onCommandUploadFinished(quint32);
	void onDownloadFinished(quint32);
private:
	void closeEvent(QCloseEvent *event);
	void displayUnRegisteredWidget();
	void displayRegisteredWidget();
private:
	Ui::QLWidget *ui;
	CtrlChannel *mCtrlChannel;
	DataChannel *mModelChannel;
	DataChannel *mCmdsChannel;
	DataChannel *mDownloadChanel;
	qint32 mTimerID;
	QString mServerIP;
	quint16 mPort;
	float mAsrLevel;
	float mCurScore;
};

#endif // WIDGET_H
