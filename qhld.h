#ifndef QHLD_H
#define QHLD_H
#include "BaseCtrl.h"
#include <QWidget>
#include <QListWidget>
#include <QObject>
#include "ui_qhld.h"
#include "qjwkeyboard.h"
#include "TimerThread.h"
#include "Config.h"
#include <qtimer.h>
#include <qstring.h>
#include "ui_qjwkeyboard.h"
#include <qlayout.h>
#include <QBuffer>
#include <QStandardItemModel>
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

class QHLD : public QWidget
{
	Q_OBJECT
		
public:
	
	QHLD( QWidget *parent=0);
	~QHLD();
	int kk=0;
	int ii=0;
	bool eventFilter(QObject *obj, QEvent *event);
	QPoint mDragPoint;
	void RollBack(int state);
	QTimer *m_pTimer;
	TimerThread *m_pTimerUpdate;
	QJWKeyboard *m_qJWKeyboard;
	QString m_latString;
	QString m_lngString;
	float m_lat;
	float m_lng;
	float m_startAngle;
	float m_spanAngle;
	float m_dis;
	int m_direction;
	int m_state;
	bool m_clc;
	int m_num;
	int m_searchType;
	void ChangeState(int state);
	void Confirm();
	void Cancel();
	void onTimerUpdate();
	void qhldshow();
	int qhldhqsz();
	int m_latTypeTemp;
	int m_lngTypeTemp;
	bool m_isError;
	void SetLat(float lat, int maybeChange=0);
	void SetLng(float lng, int maybeChange=0);
	void SetLat2(float lat, int maybeChange = 0);
	void SetLng2(float lng, int maybeChange = 0);
	void SetLat3(float lat, int maybeChange = 0);
	void SetLng3(float lng, int maybeChange = 0);
	void SetLat4(float lat, int maybeChange = 0);
	void SetLng4(float lng, int maybeChange = 0);
	void SetLat5(float lat, int maybeChange = 0);
	void SetLng5(float lng, int maybeChange = 0);
	void SetLat6(float lat, int maybeChange = 0);
	void SetLng6(float lng, int maybeChange = 0);
	void SetLat7(float lat, int maybeChange = 0);
	void SetLng7(float lng, int maybeChange = 0);
	void SetLatLng(float lat, float lng);
	void SetLatLng2(float lat, float lng);
	void SetLatLng3(float lat, float lng);
	void SetLatLng4(float lat, float lng);
	void SetLatLng5(float lat, float lng);
	void SetLatLng6(float lat, float lng);
	void SetLatLng7(float lat, float lng);
	void SetLatType(QString type);
	void SetLatType2(QString type);
	void SetLatType3(QString type);
	void SetLatType4(QString type);
	void SetLatType5(QString type);
	void SetLatType6(QString type);
	void SetLatType7(QString type);
	void SetLngType(QString type);
	void SetLngType2(QString type);
	void SetLngType3(QString type);
	void SetLngType4(QString type);
	void SetLngType5(QString type);
	void SetLngType6(QString type);
	void SetLngType7(QString type);
	void SendSignal(int state);
	void SetEmptyState(int state);
	void SetLatFabsValue(int value);
	void SetLatFabsValue2(int value);
	void SetLatFabsValue3(int value);
	void SetLatFabsValue4(int value);
	void SetLatFabsValue5(int value);
	void SetLatFabsValue6(int value);
	void SetLatFabsValue7(int value);
	void SetLngFabsValue(int value);
	void SetLngFabsValue2(int value);
	void SetLngFabsValue3(int value);
	void SetLngFabsValue4(int value);
	void SetLngFabsValue5(int value);
	void SetLngFabsValue6(int value);
	void SetLngFabsValue7(int value);	
	void SetLineEditFocus(int type);
	void Dodrag();
	void Init();
	
	void InitLineEdit();
	QString m_styleEditing;
	QString m_styleWaiting;
	QString m_styleWaiting2;
	QString m_styleError;
	QVector<QLineEdit*> m_editList;
	QLineEdit *GetCurLineEdit(int state);
	int m_curPos;
	QStandardItemModel *model;
	void SetModel(QStandardItemModel *model);
	/*void mousePressEvent(QMouseEvent * event);*/
	/*void mousePressEvent(QMouseEvent *e);*/
	void mouseMoveEvent(QMouseEvent *e);
	void dragEnterEvent(QDragEnterEvent *e);
	void dragMoveEvent(QDragMoveEvent *e);
	void dragLeaveEvent(QDragLeaveEvent *e);
	void dropEvent(QDropEvent *e);
	QVBoxLayout *layout;
	int CheckContent(int state);
public slots:
    void onString(QString string);	
	void qhldcancel();
	void qhldjdconfirm();
	void onBackspace();
	void onClear();
	void onCancel();
	void onConfirm();
	void onCursorPositionChanged(int oldPos, int newPos);
	void onTextChanged(const QString &str);
	void jia();
	void jia2();
	void jia3();
	void jia4();
	void jia5();
	void jia6();
	void jia7();
	void jia8();
	void jia9();
	void jian();
	void jian2();
	void jian3();
	void jian4();
	void jian5();
	void jian6();
	void jian7();
	void jian8();
	void jiaohuan();
	void jh1();
	void jh2();
	void jh3();
	void jh4();
	void jh5();
	void jh6();
	void jh7();
	void jh8();
signals:
	void sigQHLDSetLat(float lat);
	void sigQHLDSetLng(float lng);
	void sigQHLDSetLat2(float lat2);
	void sigQHLDSetLng2(float lng2);
	void sigQHLDSetLat3(float lat3);	
	void sigQHLDSetLng3(float lng3);
	void sigQHLDSetLat4(float lat4);
	void sigQHLDSetLng4(float lng4);
	void sigQHLDSetLat5(float lat5);
	void sigQHLDSetLng5(float lng5);
	void sigQHLDSetLat6(float lat6);
	void sigQHLDSetLng6(float lng6);
	void sigQHLDSetLat7(float lat7);
	void sigQHLDSetLng7(float lng7);
	void sigQHLDjian1();
	void sigQHLDjian2();
	void sigQHLDjian3();
	void sigQHLDjian4();
	void sigQHLDjian5();
	void sigQHLDjian6();
	void sigQHLDjian7();
	void sigqhldconfirm(int i);
private:
	Ui::QHLD ui;
};

#endif // QHLD_H
