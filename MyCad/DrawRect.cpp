#include "pch.h"
#include "DrawRect.h"


MyEdit::pStepPoint DrawRect::getPoints()	//��ȡ��
{

	return stepPoint;
}

int DrawRect::setPoint(StepPoint* point, int x, int y, COLORREF color)	//���õ�
{
	point->x = x;
	point->y = y;
	point->color = color;
	point->next = NULL;
	return 1;
}


void DrawRect::drawRect(CPoint p1, CPoint p2, CPoint p3, CPoint p4, COLORREF color)	//������
{
	
	DDALine(p1.x,p1.y, p2.x,p2.y,p3.x,p3.y,p4.x,p4.y, color);
	/*DDALine(p2.x,p2.y, p3.x,p3.y, color);
	DDALine(p3.x,p3.y, p4.x,p4.y, color);
	DDALine(p4.x,p4.y, p1.x,p1.y, color);*/

}


void DrawRect::DDALine(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, COLORREF color)	//����
{


	double dx, dy, e, x, y;
	dx = x1 - x0;
	dy = y1 - y0;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);    //��dx,dy�е����ֵ
	dx /= e;                //ÿ��������֮���ˮƽ����
	dy /= e;                //ÿ��������֮��Ĵ�ֱ����
	x = x0;
	y = y0;
	StepPoint* p = stepPoint;

	for (int i = 0; i < e; i++) //ѭ������
	{
		setPoint(p, x, y, color);   //������������õ�
		x += dx;
		y += dy;
		
		StepPoint* q = new StepPoint;	//����һ���µĵ�
		q->next = NULL;
		p->next = q;
		p = p->next;
		
	}
	dx = x2 - x1;
	dy = y2 - y1;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);    //��dx,dy�е����ֵ
	dx /= e;                //ÿ��������֮���ˮƽ����
	dy /= e;                //ÿ��������֮��Ĵ�ֱ����
	x = x1;
	y = y1;
	for (int i = 0; i < e; i++) //ѭ������
	{
		setPoint(p, x, y, color);   //������������õ�
		x += dx;
		y += dy;

		StepPoint* q = new StepPoint;	//����һ���µĵ�
		q->next = NULL;
		p->next = q;
		p = p->next;

	}
	dx = x3 - x2;
	dy = y3 - y2;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);    //��dx,dy�е����ֵ
	dx /= e;                //ÿ��������֮���ˮƽ����
	dy /= e;                //ÿ��������֮��Ĵ�ֱ����
	x = x2;
	y = y2;
	for (int i = 0; i < e; i++) //ѭ������
	{
		setPoint(p, x, y, color);   //������������õ�
		x += dx;
		y += dy;

		StepPoint* q = new StepPoint;	//����һ���µĵ�
		q->next = NULL;
		p->next = q;
		p = p->next;

	}
	dx = x0 - x3;
	dy = y0 - y3;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);    //��dx,dy�е����ֵ
	dx /= e;                //ÿ��������֮���ˮƽ����
	dy /= e;                //ÿ��������֮��Ĵ�ֱ����
	x = x3;
	y = y3;
	for (int i = 0; i < e; i++) //ѭ������
	{
		setPoint(p, x, y, color);   //������������õ�
		x += dx;
		y += dy;
		if (i < e - 1) {
			StepPoint* q = new StepPoint;	//����һ���µĵ�
			q->next = NULL;
			p->next = q;
			p = p->next;
		}
	}
	//DDALine()
}