#pragma once
#include "MyEdit.h"
class DrawRect :
    public MyEdit
{

public:
	pStepPoint stepPoint = new StepPoint;


public:
	void DDALine(int x0, int y0, int x1, int y1,int x2,int y2,int x3,int y3, COLORREF color);	//画线
	void drawRect(CPoint p1, CPoint p2, CPoint p3, CPoint p4,  COLORREF color);
	int setPoint(StepPoint* point, int x, int y, COLORREF color);//设置点
	MyEdit::pStepPoint DrawRect::getPoints();//获取点
};

