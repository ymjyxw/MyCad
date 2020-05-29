#pragma once
#include "MyEdit.h"
class DrawLine :
	public MyEdit
{
public:
	pStepPoint stepPoint = new StepPoint;

private:
	
public:
	void DrawLine::DDALine(int x0, int y0, int x1, int y1, COLORREF color);
	int DrawLine::setPoint(StepPoint* point, int x, int y, COLORREF color);//设置点
	MyEdit::pStepPoint DrawLine::getPoints();//获取点
};

