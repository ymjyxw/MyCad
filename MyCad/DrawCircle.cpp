#include "pch.h"
#include "DrawCircle.h"

void DrawCircle::MidPntCircle(int x0, int y0, int x1, int y1, COLORREF color)
{
	int x, y, d;
	x = 0;
	y = sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
	d = 1 - y;

	StepPoint* p = stepPoint;
	
	while (x < y)
	{
		
		setPoint(p, x+x0, y+y0, color);   //四舍五入后画设置点
		StepPoint* q1 = new StepPoint;	//创建一个新的点
		q1->next = NULL;
		p->next = q1;
		p = p->next;

		setPoint(p, y + x0, x + y0, color);   //四舍五入后画设置点
		StepPoint* q2 = new StepPoint;	//创建一个新的点
		q2->next = NULL;
		p->next = q2;
		p = p->next;

		setPoint(p, x + x0, -y + y0, color);   //四舍五入后画设置点
		StepPoint* q3 = new StepPoint;	//创建一个新的点
		q3->next = NULL;
		p->next = q3;
		p = p->next;

		setPoint(p, -y + x0, x + y0, color);   //四舍五入后画设置点
		StepPoint* q4 = new StepPoint;	//创建一个新的点
		q4->next = NULL;
		p->next = q4;
		p = p->next;

		setPoint(p, -x + x0, y + y0, color);   //四舍五入后画设置点
		StepPoint* q5 = new StepPoint;	//创建一个新的点
		q5->next = NULL;
		p->next = q5;
		p = p->next;

		setPoint(p, -x + x0, -y + y0, color);   //四舍五入后画设置点
		StepPoint* q6 = new StepPoint;	//创建一个新的点
		q6->next = NULL;
		p->next = q6;
		p = p->next;

		
		setPoint(p, y + x0, -x + y0, color);   //四舍五入后画设置点
		StepPoint* q7 = new StepPoint;	//创建一个新的点
		q7->next = NULL;
		p->next = q7;
		p = p->next;

		setPoint(p, -y + x0, -x + y0, color);   //四舍五入后画设置点
		StepPoint* q8 = new StepPoint;	//创建一个新的点
		q8->next = NULL;
		p->next = q8;
		p = p->next;

		if (d < 0)
		{
			d += 2 * x + 3;
			x++;
		}
		else
		{
			d += 2 * (x - y) + 5;
			x++;
			y--;
		}
		
	}
}





MyEdit::pStepPoint DrawCircle::getPoints()	//获取点
{

	return stepPoint;
}

int DrawCircle::setPoint(StepPoint* point, int x, int y, COLORREF color)	//设置点
{
	point->x = x;
	point->y = y;
	point->color = color;
	point->next = NULL;
	return 1;
}