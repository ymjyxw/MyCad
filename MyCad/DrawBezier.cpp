#include "pch.h"
#include "DrawBezier.h"



int DrawBezier::init()
{
	m_nCtrPs = 5;
	m_nSPs = 2048;
	m_pCtrPs = (CPoint*)malloc(sizeof(CPoint) * m_nCtrPs);
	m_curve = (CPoint*)malloc(sizeof(CPoint) * m_nSPs);
	
	/*for(int i=0;i<100;i++)
		_cprintf("%d\t", m_curve[i].x);*/
	return 0;
}

void DrawBezier::setBezierPoint( int m, int x, int y)
{
	m_pCtrPs[m].x = x;
	m_pCtrPs[m].y = y;
}

void DrawBezier::computeCoefficients(int n, int* c)
{

	//int k, i;       
	//for (k = 0; k <= n; k++)  //求     ! ! !k n C n k n k 
	//{
	//	c[k] = 1;          
	//	for (i = n; i >= k + 1; i--)       /*求 c[k]=n*(n-1)…(k+1) */              
	//		c[k] *= i;           
	//	for (i = n - k; i >= 2; i--)      /*求 c[k]/(n-k)!*/               
	//		c[k] /= i;
	//}
	int fenzi = n;
	int	fenmu = 1;
	c[n] = 1;
	for (int i = n - 1; i >= 0; i--)
	{
		c[i] = c[i + 1] * fenzi / fenmu;
		fenzi--;
		fenmu++;
	}
}

void DrawBezier::computePoint(float t, CPoint* pt, int nCtrPs, CPoint* pCtrPs, int* c)
{
	//pt 为所求点，nCtrPs 为控制点数目，pCtrPs 为存储控制点坐标的空间首地址    
	int i, n = nCtrPs - 1;
	float blend, t1 = 1 - t; //基函数的值    
	pt->x = 0.0;
	pt->y = 0.0;
	for (i = 0; i <= n; i++) {
		blend = c[i] * powf(t, i) * powf(t1, n - i);  /*求 C in ti(1-t)n-i */
		pt->x += pCtrPs[i].x * blend;   /*求 x(t)*/
		pt->y += pCtrPs[i].y * blend;   /*求 y(t)*/
	}
}

void DrawBezier::Bezier(CPoint* pCtrPs, int nCtrPs, int m, CPoint* curve)
{
	//m 个采样点，结果保存在 curve 所指的数组里面    
	int i;
	int* pC = (int*)malloc(nCtrPs * sizeof(int)); //分配系数的存储空间 
	computeCoefficients(nCtrPs - 1, pC);
	for (i = 0; i <= m; i++)
		computePoint(i / (float)m, &curve[i], nCtrPs, pCtrPs, pC);
	free(pC);
}









void DrawBezier::drawBezier(CPoint p1, CPoint p2, COLORREF color)
{
	init(); //初始化贝塞尔
	Bezier(m_pCtrPs, m_nCtrPs, m_nSPs, m_curve);
	setBezierPoint(0, p1.x, p1.y);
	setBezierPoint(1, (p1.x+p2.x)/4, (p1.y+(p1.y+p2.y)/2)/4);
	setBezierPoint(2, (p1.x+p2.x)/2, (p1.y+p2.y)/2);
	setBezierPoint(3, (p1.x+p2.x)*3/4, (p2.y + (p1.y + p2.y) / 2)*3 / 4);
	setBezierPoint(4, p2.x, p2.y);
	Bezier(m_pCtrPs,m_nCtrPs,m_nSPs,m_curve);
	StepPoint* p = stepPoint;

	
	for (int i = 0; i < m_nSPs; i++)
	{
		CPoint cc = m_curve[i];
		CPoint cf = m_curve[i+1];
		if (cf.x != cc.x || cf.y != cc.y) 
		{
			setPoint(p, cc.x, cc.y, color);   //四舍五入后画设置点
			StepPoint* q1 = new StepPoint;	//创建一个新的点
			q1->next = NULL;
			p->next = q1;
			p = p->next;
		}
	}
	//删除末尾结点
	p = stepPoint;
	StepPoint* q = p;
	while (p->next)
	{
		q = p;
		p = p->next;

	}
	q->next = NULL;
	free(p);

}





MyEdit::pStepPoint DrawBezier::getPoints()	//获取点
{

	return stepPoint;
}

int DrawBezier::setPoint(StepPoint* point, int x, int y, COLORREF color)	//设置点
{
	point->x = x;
	point->y = y;
	point->color = color;
	point->next = NULL;
	return 1;
}