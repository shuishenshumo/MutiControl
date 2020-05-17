#ifndef CTRLCHANNEL_H
#define CTRLCHANNEL_H

#include <QObject>

#define KEEP_ALIVE_INTERVAL (2000) /*ms*/
#define KEEP_ALIVE_CNT      (2) /* unit: KEEP_ALIVE_INTERVAL*/
#define INVALID_SESSION_ID (0xffffffff)



class QUdpSocket;

class CtrlChannel : public QObject
{
	Q_OBJECT

public:
	explicit CtrlChannel(QObject *parent = 0);
	~CtrlChannel();
	void registerCtrl();
	void unRegisterCtrl();
	void startASR();
	void stopASR();
	void savePCM(bool save);
	void switchModel();
	void switchCmdSet();
	void sendKeepAlive();
	quint32 getSessionID();
	bool isRegister() const;
	void compositePacket(QByteArray&cmd, int type, char *arg, int len);
	void sendCmd(QByteArray &cmd);
	void handleResponse(const QByteArray &resp);
	void timerEvent(QTimerEvent *event);
	QUdpSocket *mCtrlChannel;
	quint32 mSessionID;
	bool mIsRegister;
	qint32 mTimerID;
	quint32 mAliveCnt;
signals:
	void updateScore(QString);
	void updateASR(QString);
	void clientStateChanged(quint32, bool);
	void transfer(QString);
	public slots:
	void onReadyRead();



};

#endif // CTRLCHANNEL_H
