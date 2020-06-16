#include "pch.h"
#include "DrawLine.h"

	


void DrawLine::DDALine(int x0, int y0, int x1, int y1, COLORREF color)	//画线
{
	
	double dx, dy, e, x, y;
	dx = x1 - x0;
	dy = y1 - y0;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);    //求dx,dy中的最大值
	dx /= e;                //每两个像素之间的水平距离
	dy /= e;                //每两个像素之间的垂直距离
	x = x0;
	y = y0;
	StepPoint* p = stepPoint;

	for (int i = 0; i < e; i++) //循环画线
	{
		setPoint(p, x, y, color);   //四舍五入后画设置点
		x += dx;
		y += dy;
		if (i < e - 1) {
			StepPoint* q = new StepPoint;	//创建一个新的点
			q->next = NULL;
			p->next = q;
			p = p->next;
		}
	}
}


MyEdit::pStepPoint DrawLine::getPoints()	//获取点
{

	return stepPoint;
}

int DrawLine::setPoint(StepPoint* point, int x, int y, COLORREF color)	//设置点
{
	point->x = x;
	point->y = y;
	point->color = color;
	point->next = NULL;
	return 1;
}