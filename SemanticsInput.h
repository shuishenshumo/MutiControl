#ifndef SEMANTICSINPUT_H
#define SEMANTICSINPUT_H

#include <QThread>

class SemanticsInput : public QThread
{
	Q_OBJECT

public:
	SemanticsInput(QObject *parent);
	~SemanticsInput();

	void stop();
protected:
	void run();
private:
	volatile bool stopped;

public slots:

signals :

};

#endif // SEMANTICSINPUT_H
