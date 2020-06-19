#include "pch.h"
#include "DrawFillRect.h"

void DrawFillRect::DrawRectFunc(int x0, int y0, int x1, int y1, COLORREF color)
{
    StepPoint* p = stepPoint; //��ȡͷ���
    if (x0 > x1)
    {
        int x;
        x = x1;
        x1 = x0;
        x0 = x;
    }
    if (y0 > y1)
    {
        int y;
        y = y1;
        y1 = y0;
        y0 = y;
    }
    for (int i = y0; i < y1; i++)
    {
        for (int j = x0; j < x1; j++)
        {
            setPoint(p, j, i, color);   //д�������ݵ�������
            if (!(i == y1 - 1 && j == x1 - 1))
            {
                StepPoint* q = new StepPoint;	//����һ���µĵ�
                q->next = NULL;
                p->next = q;
                p = p->next;
            }
        }
    }


}
//������д������ڲ�
int DrawFillRect::setPoint(StepPoint* point, int x, int y, COLORREF color)
{
    point->x = x;
    point->y = y;
    point->color = color;
    point->next = NULL;
    return 1;
}

//����ͷ���
MyEdit::pStepPoint DrawFillRect::getPoints()
{
    return stepPoint;
}
