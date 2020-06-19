#include "pch.h"
#include "DrawFillRect.h"

void DrawFillRect::DrawRectFunc(int x0, int y0, int x1, int y1, COLORREF color)
{
    StepPoint* p = stepPoint; //获取头结点
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
            setPoint(p, j, i, color);   //写入点的数据到链表中
            if (!(i == y1 - 1 && j == x1 - 1))
            {
                StepPoint* q = new StepPoint;	//创建一个新的点
                q->next = NULL;
                p->next = q;
                p = p->next;
            }
        }
    }


}
//把数据写到结点内部
int DrawFillRect::setPoint(StepPoint* point, int x, int y, COLORREF color)
{
    point->x = x;
    point->y = y;
    point->color = color;
    point->next = NULL;
    return 1;
}

//返回头结点
MyEdit::pStepPoint DrawFillRect::getPoints()
{
    return stepPoint;
}
