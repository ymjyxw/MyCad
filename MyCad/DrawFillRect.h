#pragma once
#include "MyEdit.h"
class DrawFillRect :
    public MyEdit
{
public:
	pStepPoint stepPoint = new StepPoint;//存储填充矩形的点

private:

public:
	void DrawFillRect::DrawRectFunc(int x0, int y0, int x1, int y1, COLORREF color);	//绘制矩形的函数
																			int DrawFillRect::setPoint(StepPoint* point, int x, int y, COLORREF color);//设置点
	MyEdit::pStepPoint DrawFillRect::getPoints();//获取点
};

