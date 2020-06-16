#pragma once
#include "MyEdit.h"
#include <wtypes.h>

class DrawCircle :
    public MyEdit
{
public:
	pStepPoint stepPoint = new StepPoint;

private:

public:
	void MidPntCircle(int x0, int y0, int x1, int y1, COLORREF color);
	
	int setPoint(StepPoint* point, int x, int y, COLORREF color);//设置点
	MyEdit::pStepPoint DrawCircle::getPoints();//获取点



};

