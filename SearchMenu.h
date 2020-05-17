#ifndef SEARCHMENU_H
#define SEARCHMENU_H

#include "BaseCtrl.h"
#include <QWidget>

#define SEARCH_MENU_DIS  (100)	//同心圆（防止控制点）半径增加量
#define SEARCH_MENU_RADIUS (40)

class SearchMenu : public BaseCtrl
{
	Q_OBJECT

public:
	SearchMenu(QWidget *parent);
	~SearchMenu();

	typedef enum
	{
		NONE = 0,
		SX,
		PT,
		HX
	}SEARCH_TYPE;

	void Draw();
	void Refresh();

	int OnPress(QPointF point);
	int OnRelease(QPointF point);
	int OnMove(QPointF pointOld, QPointF pointNew);

	int SectionIndex(QPointF point);

signals:
	void sigSetSearchType(int);

private:
	//
	QRectF m_sectionSearch1;
	QRectF m_sectionSearch2;
	QRectF m_sectionSearch3;

	//
	QImage *m_pImageSearch1;
	QImage *m_pImageSearch2;
	QImage *m_pImageSearch3;

	//控制激活区域
	SEARCH_TYPE m_selectedType;

	int m_state;

};

#endif