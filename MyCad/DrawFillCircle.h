#pragma once
#include "MyEdit.h"
class DrawFillCircle :
    public MyEdit
{
public:
	pStepPoint stepPoint = new StepPoint;//�洢�����εĵ�

private:

public:
	void DrawFillCircle::drawFillCircle(int x0, int y0, int x1, int y1, COLORREF color);	//���ƾ��εĺ���
	int DrawFillCircle::setPoint(StepPoint* point, int x, int y, COLORREF color);//���õ�
	MyEdit::pStepPoint DrawFillCircle::getPoints();//��ȡ��
};

