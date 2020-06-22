#include "pch.h"
#include "DrawRect.h"


MyEdit::pStepPoint DrawRect::getPoints()	//获取点
{

	return stepPoint;
}

int DrawRect::setPoint(StepPoint* point, int x, int y, COLORREF color)	//设置点
{
	point->x = x;
	point->y = y;
	point->color = color;
	point->next = NULL;
	return 1;
}


void DrawRect::drawRect(CPoint p1, CPoint p2, CPoint p3, CPoint p4, COLORREF color)	//画矩形
{
	
	DDALine(p1.x,p1.y, p2.x,p2.y,p3.x,p3.y,p4.x,p4.y, color);
	/*DDALine(p2.x,p2.y, p3.x,p3.y, color);
	DDALine(p3.x,p3.y, p4.x,p4.y, color);
	DDALine(p4.x,p4.y, p1.x,p1.y, color);*/

}


void DrawRect::DDALine(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, COLORREF color)	//画线
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
		
		StepPoint* q = new StepPoint;	//创建一个新的点
		q->next = NULL;
		p->next = q;
		p = p->next;
		
	}
	dx = x2 - x1;
	dy = y2 - y1;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);    //求dx,dy中的最大值
	dx /= e;                //每两个像素之间的水平距离
	dy /= e;                //每两个像素之间的垂直距离
	x = x1;
	y = y1;
	for (int i = 0; i < e; i++) //循环画线
	{
		setPoint(p, x, y, color);   //四舍五入后画设置点
		x += dx;
		y += dy;

		StepPoint* q = new StepPoint;	//创建一个新的点
		q->next = NULL;
		p->next = q;
		p = p->next;

	}
	dx = x3 - x2;
	dy = y3 - y2;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);    //求dx,dy中的最大值
	dx /= e;                //每两个像素之间的水平距离
	dy /= e;                //每两个像素之间的垂直距离
	x = x2;
	y = y2;
	for (int i = 0; i < e; i++) //循环画线
	{
		setPoint(p, x, y, color);   //四舍五入后画设置点
		x += dx;
		y += dy;

		StepPoint* q = new StepPoint;	//创建一个新的点
		q->next = NULL;
		p->next = q;
		p = p->next;

	}
	dx = x0 - x3;
	dy = y0 - y3;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);    //求dx,dy中的最大值
	dx /= e;                //每两个像素之间的水平距离
	dy /= e;                //每两个像素之间的垂直距离
	x = x3;
	y = y3;
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
	//DDALine()
}