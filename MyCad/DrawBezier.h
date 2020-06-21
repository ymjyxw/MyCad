#pragma once
#include "MyEdit.h"
class DrawBezier :
    public MyEdit
{
public:
	pStepPoint stepPoint = new StepPoint;

	int m_nCtrPs;//（控制点数目）
	int	m_nSPs;	// （采样点数目）
	CPoint* m_pCtrPs; //（控制点坐标）
	CPoint* m_curve;// （全部采样点坐标）

	
	int init();		//初始化曲线
	void setBezierPoint( int m, int x, int y);	//设置曲线第m控制点坐标为（x，y）
	void computeCoefficients(int n, int* c); //计算系数, n 为控制点数目，c 为存储空间的首地址，存储内容为系数 
	void computePoint(float t, CPoint* pt, int nCtrPs, CPoint* pCtrPs, int* c); //计算 Bezier 曲线上参数为 t 的点

	void Bezier(CPoint* pCtrPs, int nCtrPs, int m, CPoint* curve); //计算 Bezier 曲线上所有采样点,m 个采样点，结果保存在 curve 所指的数组里面 



public:

	void DrawBezier::drawBezier(CPoint p1,CPoint p2,COLORREF color);
	int DrawBezier::setPoint(StepPoint* point, int x, int y, COLORREF color);//设置点
	MyEdit::pStepPoint DrawBezier::getPoints();//获取点

	
};

