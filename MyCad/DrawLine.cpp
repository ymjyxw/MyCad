#include "pch.h"
#include "DrawLine.h"

	


void DrawLine::DDALine(int x0, int y0, int x1, int y1, COLORREF color)	//����
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
		if (i < e - 1) {
			StepPoint* q = new StepPoint;	//����һ���µĵ�
			q->next = NULL;
			p->next = q;
			p = p->next;
		}
	}
}


MyEdit::pStepPoint DrawLine::getPoints()	//��ȡ��
{

	return stepPoint;
}

int DrawLine::setPoint(StepPoint* point, int x, int y, COLORREF color)	//���õ�
{
	point->x = x;
	point->y = y;
	point->color = color;
	point->next = NULL;
	return 1;
}