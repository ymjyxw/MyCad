#pragma once
#include "MyEdit.h"
class DrawFillRect :
    public MyEdit
{
public:
	pStepPoint stepPoint = new StepPoint;//�洢�����εĵ�

private:

public:
	void DrawFillRect::DrawRectFunc(int x0, int y0, int x1, int y1, COLORREF color);	//���ƾ��εĺ���
																			int DrawFillRect::setPoint(StepPoint* point, int x, int y, COLORREF color);//���õ�
	MyEdit::pStepPoint DrawFillRect::getPoints();//��ȡ��
};

