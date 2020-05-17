#ifndef GRAMMARINPUT_H
#define GRAMMARINPUT_H

#include <QThread>

class GrammarInput : public QThread
{
	Q_OBJECT

public:
	GrammarInput(QObject *parent);
	~GrammarInput();

	void stop();
protected:
	void run();
private:
	volatile bool stopped;

public slots:

signals :

};

#endif // GRAMMARINPUT_H
