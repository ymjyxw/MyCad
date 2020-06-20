#include "pch.h"
#include "DrawFillCircle.h"

void DrawFillCircle::drawFillCircle(int x0, int y0, int x1, int y1, COLORREF color)
{
    int x = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
    int y = 0;
    int xChange = 1 - (x << 1);
    int yChange = 0;
    int radiusError = 0;
    StepPoint* p = stepPoint;
    while (x >= y)
    {
        for (int i = x0 - x; i <= x0 + x; i++)
        {
            /*SetPixel(i, y0 + y);
            SetPixel(i, y0 - y);*/
            setPoint(p,i, y0 + y, color);
            StepPoint* q1 = new StepPoint;	//创建一个新的点
            q1->next = NULL;
            p->next = q1;
            p = p->next;
            setPoint(p,i, y0 - y, color);
            StepPoint* q2 = new StepPoint;	//创建一个新的点
            q2->next = NULL;
            p->next = q2;
            p = p->next;

        }
        for (int i = x0 - y; i <= x0 + y; i++)
        {
            /*SetPixel(i, y0 + x);
            SetPixel(i, y0 - x);*/
            setPoint(p, i, y0 + x, color);
            StepPoint* q3 = new StepPoint;	//创建一个新的点
            q3->next = NULL;
            p->next = q3;
            p = p->next;
            setPoint(p, i, y0 - x, color);
            StepPoint* q4 = new StepPoint;	//创建一个新的点
            q4->next = NULL;
            p->next = q4;
            p = p->next;
        }

        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
    //删除末尾结点
    p = stepPoint;
    StepPoint *q = p;
    while (p->next)
    {
        q = p;
        p = p->next;
        
    }
    q->next = NULL;
    free(p);
}


MyEdit::pStepPoint DrawFillCircle::getPoints()	//获取点
{

    return stepPoint;
}

int DrawFillCircle::setPoint(StepPoint * point, int x, int y, COLORREF color)	//设置点
{
    point->x = x;
    point->y = y;
    point->color = color;
    point->next = NULL;
    return 1;
}