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
		
		setPoint(p, x+x0, y+y0, color);   //������������õ�
		StepPoint* q1 = new StepPoint;	//����һ���µĵ�
		q1->next = NULL;
		p->next = q1;
		p = p->next;

		setPoint(p, y + x0, x + y0, color);   //������������õ�
		StepPoint* q2 = new StepPoint;	//����һ���µĵ�
		q2->next = NULL;
		p->next = q2;
		p = p->next;

		setPoint(p, x + x0, -y + y0, color);   //������������õ�
		StepPoint* q3 = new StepPoint;	//����һ���µĵ�
		q3->next = NULL;
		p->next = q3;
		p = p->next;

		setPoint(p, -y + x0, x + y0, color);   //������������õ�
		StepPoint* q4 = new StepPoint;	//����һ���µĵ�
		q4->next = NULL;
		p->next = q4;
		p = p->next;

		setPoint(p, -x + x0, y + y0, color);   //������������õ�
		StepPoint* q5 = new StepPoint;	//����һ���µĵ�
		q5->next = NULL;
		p->next = q5;
		p = p->next;

		setPoint(p, -x + x0, -y + y0, color);   //������������õ�
		StepPoint* q6 = new StepPoint;	//����һ���µĵ�
		q6->next = NULL;
		p->next = q6;
		p = p->next;

		
		setPoint(p, y + x0, -x + y0, color);   //������������õ�
		StepPoint* q7 = new StepPoint;	//����һ���µĵ�
		q7->next = NULL;
		p->next = q7;
		p = p->next;

		setPoint(p, -y + x0, -x + y0, color);   //������������õ�
		StepPoint* q8 = new StepPoint;	//����һ���µĵ�
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





MyEdit::pStepPoint DrawCircle::getPoints()	//��ȡ��
{

	return stepPoint;
}

int DrawCircle::setPoint(StepPoint* point, int x, int y, COLORREF color)	//���õ�
{
	point->x = x;
	point->y = y;
	point->color = color;
	point->next = NULL;
	return 1;
}