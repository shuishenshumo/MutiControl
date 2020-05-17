#include "ctrlchannel.h"
#include "msg.h"
#include <QUdpSocket>

#include <qnetworkdatagram.h>
#include <QtEndian>
#include <QDebug>
#include <QDomDocument>
#include <QTimerEvent>
#include "SpeechYZS.h"



CtrlChannel::CtrlChannel(QObject *parent) : QObject(parent),
mCtrlChannel(new QUdpSocket(parent)),
mSessionID(-1),
mIsRegister(false),
mAliveCnt(0)
{
	connect(mCtrlChannel, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	
}

CtrlChannel::~CtrlChannel() {
	mCtrlChannel->deleteLater();
}

void CtrlChannel::sendCmd(QByteArray &cmd) {
	mCtrlChannel->writeDatagram(cmd, QHostAddress("192.168.8.230"), 8080);
}

void CtrlChannel::onReadyRead() {
	
	while (mCtrlChannel->hasPendingDatagrams()) {
		
		QByteArray datagram;
		QHostAddress sender;
		quint16 port;
		datagram.resize(mCtrlChannel->pendingDatagramSize());
		
		mCtrlChannel->readDatagram(datagram.data() , datagram.size(), &sender, &port);
		/*QByteArray datagram2; 
	
		datagram = datagram2 .append(datagram2);
		qDebug() << datagram;
		qDebug() << datagram2;*/
		handleResponse(datagram);
		
	}
}

void CtrlChannel::compositePacket(QByteArray&cmd, int type, char *arg, int len) {
	int msgLen = sizeof(request_head_t) + len;
	quint32 session_id = qToBigEndian<quint32>(mSessionID);
	type = qToBigEndian<quint32>(type);
	cmd.append((char *)&type, sizeof(type));
	cmd.append((char *)&session_id, sizeof(session_id));
	msgLen = qToBigEndian<quint32>(msgLen);
	cmd.append((char *)&msgLen, sizeof(msgLen));
	if (arg) {
		cmd.append(arg, len);
	}
}

void CtrlChannel::registerCtrl() {
	if (!mIsRegister) {
		QByteArray cmd;
		mAliveCnt = 0;
		compositePacket(cmd, ASR_SESSION_REGISTER, NULL, 0);
		sendCmd(cmd);
	}
}

void CtrlChannel::unRegisterCtrl() {
	if (mIsRegister) {
		QByteArray cmd;
		compositePacket(cmd, ASR_SESSION_UNREGISTER, NULL, 0);
		sendCmd(cmd);
		killTimer(mTimerID);
		mIsRegister = false;
		mAliveCnt = 0;
	}
}

void CtrlChannel::startASR() {
	QByteArray cmd;
	compositePacket(cmd, CAPTURE_START, NULL, 0);
	sendCmd(cmd);
	/*qDebug() << 1;*/
}

void CtrlChannel::stopASR() {
	QByteArray cmd;
	compositePacket(cmd, CAPTURE_STOP, NULL, 0);
	sendCmd(cmd);
}

void CtrlChannel::savePCM(bool save) {
	QByteArray cmd;
	char args = (char)save;
	compositePacket(cmd, ASR_PCM_SAVE, &args, sizeof(args));
	sendCmd(cmd);
}

void CtrlChannel::switchModel() {
	QByteArray cmd;
	compositePacket(cmd, ASR_MODEL_SWITCH, NULL, 0);
	sendCmd(cmd);
}

void CtrlChannel::switchCmdSet() {
	QByteArray cmd;
	compositePacket(cmd, ASR_CMDS_SWITCH, NULL, 0);
	sendCmd(cmd);
}

void CtrlChannel::handleResponse(const QByteArray &resp) 
{   

	
	
	reponse_head_t msg_head;
	memcpy(&msg_head, resp, sizeof(msg_head));

	msg_head.type = qFromBigEndian<quint32>(msg_head.type);
	msg_head.session_id = qFromBigEndian<quint32>(msg_head.session_id);
	msg_head.len = qFromBigEndian<quint32>(msg_head.len);

	/*QString str = (resp.data() + sizeof(msg_head));
	qDebug() << str;
	emit transfer(str);*/
	
	if (msg_head.type == ASR_RESULT_SCORE_NOTIFY) {
		/*qDebug() << "score:" << (resp.data() + sizeof(msg_head));*/
		qDebug() << 4;
		emit updateScore((resp.data() + sizeof(msg_head)));
	}
	else if (msg_head.type == ASR_RESULT_DATA_NOTIFY) {
		
		qDebug() << "result:" << (resp.data() + sizeof(msg_head));
		QString str = (resp.data() + sizeof(msg_head));
		qDebug() << str;
		emit transfer(str);
		QString result(resp.data() + sizeof(msg_head));
		QString asr;
		QDomDocument doc;
		doc.setContent(result);
		QDomElement docElem = doc.documentElement();
		QDomNode node = docElem.firstChild();
		while (!node.isNull()) {
			QDomElement e = node.toElement();
			if (!e.isNull()) {
				qDebug() << e.text();
				asr.append(e.text());
			}
			node = node.nextSibling();
		}
		/*qDebug() << "asr report:" << asr;*/
		emit updateASR(asr);
	}
	else if ((msg_head.type == ASR_SESSION_REGISTER_RESP)
		&& (msg_head.session_id != INVALID_SESSION_ID)) {
		mSessionID = msg_head.session_id;
		mIsRegister = true;
		mTimerID = startTimer(KEEP_ALIVE_INTERVAL);
		emit clientStateChanged(mSessionID, true);
		qDebug() << 5;
	}
	else if ((msg_head.type == ASR_SESSION_ALIVE_RESP)) {
		qDebug() << 6;
		mAliveCnt = 0;
	}
	else {
		qDebug() << "resp type:" << msg_head.type
			<< "len:" << msg_head.len
			<< "session_id:" << msg_head.session_id;
	}
}

quint32 CtrlChannel::getSessionID() {
	return mSessionID;
}

bool CtrlChannel::isRegister() const {
	return mIsRegister;
}

void CtrlChannel::sendKeepAlive() {
	QByteArray cmd;
	compositePacket(cmd, ASR_KEEP_ALIVE, NULL, 0);
	sendCmd(cmd);
}

void CtrlChannel::timerEvent(QTimerEvent *event) {
	if (event->timerId() != mTimerID) {
		return;
	}
	if (mIsRegister) {
		mAliveCnt++;
		if (mAliveCnt > KEEP_ALIVE_CNT) {
			mIsRegister = false;
			emit clientStateChanged(mSessionID, false);
		}
		//qDebug() << "send keeplive";
		sendKeepAlive();
	}
}
