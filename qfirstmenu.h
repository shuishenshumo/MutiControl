#ifndef QFIRSTMENU_H
#define QFIRSTMENU_H

#include <QWidget>
#include "ui_qfirstmenu.h"

class QFirstMenu : public QWidget
{
	Q_OBJECT

public:
	typedef enum
	{
		RESCUE = 1,
		DIRECT_FLIHT,
		SEARCH,
		COORDINATION
	}QFIRSTMENU_MODE;

public:
	QFirstMenu(QWidget *parent = 0);
	~QFirstMenu();

	
signals:
	void sigSelectMode(int mode);

public slots:
	void onSelectMode();

private:
	Ui::QFirstMenu ui;
};

#endif // QFIRSTMENU_H
