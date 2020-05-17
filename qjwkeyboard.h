#ifndef QJWKEYBOARD_H
#define QJWKEYBOARD_H

#include <QWidget>
#include <qstring.h>
#include <qtimer.h>
#include "ui_qjwkeyboard.h"

class QJWKeyboard : public QWidget
{
	Q_OBJECT

public:
	QJWKeyboard(QWidget *parent = 0);
	~QJWKeyboard();

	QTimer* m_timer;

	int m_state;
	void SetState(int state);
	void Confirm();
	void Cancel();

	void SetLatType(int type);
	void SetLngType(int type);

	void SetTip(QString str);

signals:
	void sigString(QString s);
	void sigBackspace();
	void sigCancel();
	void sigConfirm();
	
public slots:
	void onKeyboardMsg();
	void onStartDelete();
	void onStopDelete();
	void onTimer();

private:
	Ui::QJWKeyboard ui;
};

#endif // QJWKEYBOARD_H
