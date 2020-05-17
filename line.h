#ifndef LINE_H
#define LINE_H

#include "BaseCtrl.h"
#include <QVector>
#include <qpoint.h>

class Line: public BaseCtrl
{
	
	Q_OBJECT
public:
	Line(QWidget *parent);
	~Line();

	void FrameInit();
	void Draw();
	void Draw2();
	void Draw3();
	void Draw4();
	void Draw5();
	void Draw6();
	void Refresh();
	void getline(int x, int y, int xx, int yy);
	void getline2(int x, int y, int xx, int yy);
	void getline3(int x, int y, int xx, int yy);
	void getline4(int x, int y, int xx, int yy);
	void getline5(int x, int y, int xx, int yy);
	void getline6(int x, int y, int xx, int yy);
};

#endif