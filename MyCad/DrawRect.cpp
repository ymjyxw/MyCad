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


void DrawRect::drawRect(int x0, int y0, int x1, int y1, COLORREF color)	//������
{
	int xl, xr, yb, yt, x, y, e, d = 1;
	xr = max(x0, x1);
	xl = min(x0, x1);
	yt = max(y0, y1);
	yb = min(y0, y1);
	e = 2 * ((xr - xl) + (yt - yb));//�ܳ�
	x = xl;
	y = yb;
	StepPoint* p = stepPoint;
	for (int i = 0; i < e; i++) //ѭ������
	{
		setPoint(p, x, y, color);   //������������õ�
		switch (d) {//������
		case 1: {
			y += 1;
			if (y == yt) {
				d += 1;
				break;
			}
		}break;
		case 2: {
			x += 1;
			if (x == xr) {
				d += 1;
				break;
			}
		}break;
		case 3: {
			y -= 1;
			if (y == yb) {
				d += 1;
				break;
			}
		}break;
		case 4: {
			x -= 1;
			if (y == xl) {
				d = 1;
				break;
			}
		}break;
		}

		if (i < e - 1) {
			StepPoint* q = new StepPoint;	//����һ���µĵ�
			q->next = NULL;
			p->next = q;
			p = p->next;
		}
	}
}