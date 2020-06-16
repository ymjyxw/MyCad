#pragma once
#include "MyEdit.h"
class DrawRect :
    public MyEdit
{

public:
	pStepPoint stepPoint = new StepPoint;


public:
	void drawRect(int x0, int y0, int x1, int y1, COLORREF color);
	int setPoint(StepPoint* point, int x, int y, COLORREF color);//设置点
	MyEdit::pStepPoint DrawRect::getPoints();//获取点
};

