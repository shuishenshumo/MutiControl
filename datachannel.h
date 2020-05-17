#ifndef DATACHANNEL_H
#define DATACHANNEL_H

#include <QObject>
#include <QFile>

#define DATA_BLOCK_SIZE (2048)
class QTcpSocket;
class QHostAddress;

class DataChannel : public QObject
{
	Q_OBJECT
public:
	enum DataTransferType {
		DataTransferlModels,
		DataTransferCmds,
		DataTransferPcm
	};
	explicit DataChannel(QObject *parent = 0);
	~DataChannel();
	void connectToHost(const QHostAddress &address, quint16 port,
		DataTransferType dataType, const QString& fileName);
signals:
	void uploadFinished(quint32);
	void downloadFinished(quint32);
	public slots:
	void onConnected();
	void onBytesWritten(qint64);
	void onReadyRead();
	void onDisconnected();
	void onClientStateChanged(quint32, bool);
private:
	bool IsChannelConnected();
	void sendUploadHead(DataTransferType datatype);
	void sendModelsHead();
	void sendCmdsHead();
	void sendPcmHead();
	QByteArray calcMd5();
private:
	QTcpSocket *mDataChannel;
	quint32 mSessionID;
	bool mIsRegister;
	quint32 mSendCnt;
	quint32 mRecvCnt;
	bool mIsConnected;
	QString mFileName;
	QFile mDataFile;
	DataTransferType mDataType;
	bool mIsRecvedHead;
	quint32 mTotalSize;
};

#endif // DATACHANNEL_H
