#ifndef QFANSHAPED_H
#define QFANSHAPED_H

#include <QWidget>
#include "ui_qfanshaped.h"

#include "qjwkeyboard.h"
#include "TimerThread.h"
#include "Config.h"

class QFanShaped : public QWidget
{
	Q_OBJECT

public:
	QFanShaped(QWidget *parent = 0);
	~QFanShaped();

	//bool event(QEvent *ev);
	bool eventFilter(QObject *obj, QEvent *event);

	void InitStyle();

	//
	TimerThread *m_pTimerUpdate;

	//
	void InitLineEdit();	
	QString m_styleEditing;
	QString m_styleWaiting;
	QString m_styleError;
	QVector<QLineEdit*> m_editList;
	QLineEdit *GetCurLineEdit(int state);
	void ChangeState(int state);
	int m_curPos;

	//
	int m_state;

	QJWKeyboard *m_qJWKeyboard;
	QString m_latString;
	QString m_lngString;

	float m_lat;
	float m_lng;
	float m_startAngle;
	float m_spanAngle;
	float m_dis;
	int m_direction;
	int m_num;

	int m_searchType;	//搜索类型，1表示扇形搜索，2表示爬梯搜索，3表示盒形搜索

	void SetLat(float lat, int maybeChange = 0);
	void SetLng(float lng, int maybeChange = 0);
	void SetStartAngle(float startAngle, int maybeChange = 0);
	void SetSpanAngle(float spanAngle, int maybeChange = 0);
	void SetDis(float dis, int maybeChange = 0);
	void SetDirection(int direction);

	int m_latTypeTemp;
	int m_lngTypeTemp;
	void SetLatType(QString type);
	void SetLngType(QString type);
	void SetLatFabsValue(int value);
	void SetLngFabsValue(int value);

	void SetClock(int i);

	void SetSearchMode(int i);
	void SetNum(int num);

	void AddNum();
	void MinusNum();

	//文本框回滚
	void RollBack(int state);

	//文本框激活事件
	void SendSignal(int state);


	void SetLineEditFocus(int type);

	void Confirm();
	void Cancel();

	//
	bool m_isError;

	void SetEmptyState(int state);

	int CheckContent(int state);


public slots:

	//接收QJWKeyboard的消息
	void onString(QString string);
	void onClear();
	void onBackspace();
	void onConfirm();
	void onCancel();

	//取消计划
	void onCancelSearch();

	//执行搜索
	void onActSearch();

	//文本框改变
	void onTextChanged(const QString &str);

	//搜索模式改变
	void onSelectSearchMode();

	//搜索方向改变
	void onSwitchClock();

	//
	void onChangeNum();

	//
	void onTimerUpdate();

	//
	void onCursorPositionChanged(int oldPos, int newPos);

signals:
	void sigQFanShapedSetLat(float lat);
	void sigQFanShapedSetLng(float lng);
	void sigQFanShapedSetStartAngle(float startAngle);
	void sigQFanShapedSetSpanAngle(float spanAngle);
	void sigQFanShapedSetDis(float dis);
	void sigQFanShapedSetDirection(int direction);

	void sigCancelSearch(int);
	void sigActSearch(int);

private:
	Ui::QFanShaped ui;
};

#endif // QFANSHAPED_H
