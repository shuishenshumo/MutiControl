#include "datachannel.h"
#include "msg.h"
#include <QTcpSocket>
#include <QtEndian>
#include <QFileInfo>
#include <QCryptographicHash>

DataChannel::DataChannel(QObject *parent) : QObject(parent),
mDataChannel(new QTcpSocket(this)),
mSessionID(-1),
mSendCnt(0),
mRecvCnt(0),
mIsConnected(false)
{
	connect(mDataChannel, SIGNAL(connected()), this, SLOT(onConnected()));
	connect(mDataChannel, SIGNAL(bytesWritten(qint64)), SLOT(onBytesWritten(qint64)));
	connect(mDataChannel, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	connect(mDataChannel, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

void DataChannel::sendUploadHead(DataTransferType datatype) {
	QByteArray data;
	quint32 type;
	request_head_t request;
	QByteArray md5 = calcMd5();
	mDataFile.setFileName(mFileName);
	mDataFile.open(QIODevice::ReadOnly);
	qDebug() << mFileName << "'s md5" << md5;
	if (datatype == DataTransferCmds) {
		type = FILE_TRANSFER_CMDS;
	}
	else {
		type = FILE_TRANSFER_MODEL;
	}
	request.type = qToBigEndian<quint32>(type);
	request.session_id = qToBigEndian<quint32>(mSessionID);
	request.len = (quint32)mDataFile.size() + sizeof(request_head_t) + md5.size();
	qDebug() << "msg size " << request.len;
	request.len = qToBigEndian<quint32>(request.len);
	data.append((char *)&request, sizeof(request));
	data.append(md5);
	mDataChannel->write(data);
	mSendCnt = 0;
}

void DataChannel::sendModelsHead() {
	sendUploadHead(DataTransferlModels);
}

void DataChannel::sendCmdsHead() {
	sendUploadHead(DataTransferCmds);
}

void DataChannel::sendPcmHead() {
	QByteArray data;
	request_head_t request;
	mDataFile.setFileName(mFileName);
	mDataFile.open(QIODevice::WriteOnly);
	request.type = qToBigEndian<quint32>(FILE_TRANSFER_PCM);
	request.session_id = qToBigEndian<quint32>(mSessionID);
	request.len = sizeof(request_head_t);
	qDebug() << "msg size " << request.len;
	request.len = qToBigEndian<quint32>(request.len);
	data.append((char *)&request, sizeof(request));
	mDataChannel->write(data);
	mRecvCnt = 0;
	mIsRecvedHead = 0;
}

void DataChannel::onConnected() {
	mIsConnected = true;
	if (mDataType == DataTransferCmds) {
		qDebug() << "data channel cmds connected";
		sendCmdsHead();
	}
	else if (mDataType == DataTransferlModels) {
		qDebug() << "data channel modes connected";
		sendModelsHead();
	}
	else if (mDataType == DataTransferPcm) {
		qDebug() << "data channel pcm connected";
		sendPcmHead();
	}
}

void DataChannel::onBytesWritten(qint64) {
	QByteArray data;
	if ((mDataType == DataTransferlModels) || (mDataType == DataTransferCmds)) {
		if (!mDataFile.atEnd()) {
			data = mDataFile.read(DATA_BLOCK_SIZE);
			mDataChannel->write(data);
		}
		else {
			mDataFile.close();
			emit uploadFinished(1);
		}
	}
}

void DataChannel::onReadyRead() {
	if (mDataType == DataTransferPcm) {
		if ((!mIsRecvedHead) && (mDataChannel->bytesAvailable() >= sizeof(reponse_head_t))) {
			reponse_head_t resp_head;
			mIsRecvedHead = true;
			int ret;
			ret = mDataChannel->read((char *)&resp_head, sizeof(resp_head));
			if (ret >= 0) {
				mRecvCnt += sizeof(resp_head);
				mTotalSize = qFromBigEndian<quint32>(resp_head.len);
				qDebug() << "pcm file size" << mTotalSize;
			}
		}
		else if (mIsRecvedHead) {
			QByteArray data = mDataChannel->readAll();
			mDataFile.write(data);
			mRecvCnt += data.size();
			if (mRecvCnt == mTotalSize) {
				qDebug() << "success to load asr.pcm";
				mDataFile.close();
				mIsRecvedHead = false;
				emit downloadFinished(1);
			}
		}
	}
}

void DataChannel::onDisconnected() {
	mIsConnected = false;
	if ((mDataType == DataTransferlModels) || (mDataType == DataTransferCmds)) {
		emit uploadFinished(1);
	}
	else {
		emit downloadFinished(1);
	}
	qDebug() << "data channel closed";
}

DataChannel::~DataChannel() {
	mDataChannel->deleteLater();
}

bool DataChannel::IsChannelConnected() {
	return mIsConnected;
}

void DataChannel::connectToHost(const QHostAddress &address,
	quint16 port, DataTransferType dataType,
	const QString& fileName) {
	if (!mIsConnected) {
		mDataChannel->connectToHost(address, port);
		mDataType = dataType;
		mFileName = fileName;
	}
}

void DataChannel::onClientStateChanged(quint32 sessionID, bool alive) {
	qDebug() << sessionID << alive;
	if (alive) {
		mSessionID = sessionID;
	}
	else {
		if (IsChannelConnected()) {
			mDataChannel->close();
		}
	}
}

QByteArray DataChannel::calcMd5() {
	QFile localFile(mFileName);

	if (!localFile.open(QFile::ReadOnly)) {
		qDebug() << "file open error.";
		return 0;
	}
	QCryptographicHash ch(QCryptographicHash::Md5);
	quint64 totalBytes = 0;
	quint64 bytesWritten = 0;
	quint64 bytesToWrite = 0;
	quint64 loadSize = 1024 * 4;
	QByteArray buf;
	totalBytes = localFile.size();
	bytesToWrite = totalBytes;
	while (1){
		if (bytesToWrite > 0) {
			buf = localFile.read(qMin(bytesToWrite, loadSize));
			ch.addData(buf);
			bytesWritten += buf.length();
			bytesToWrite -= buf.length();
			buf.resize(0);
		}
		else {
			break;
		}
		if (bytesWritten == totalBytes) {
			break;
		}
	}
	localFile.close();
	return ch.result().toHex();
}
