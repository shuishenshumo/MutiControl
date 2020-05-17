#include "GrammarInput.h"

GrammarInput::GrammarInput(QObject *parent)
	: QThread(parent)
{
	stopped = false;
}

GrammarInput::~GrammarInput()
{

}

void GrammarInput::run()
{
	while (!stopped)
	{
		sleep(10);
	}
}

void GrammarInput::stop()
{
	stopped = true;
}