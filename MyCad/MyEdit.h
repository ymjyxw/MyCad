#pragma once


class MyEdit
{
public :
	typedef struct StepPoint	//像素点链表
	{	
		int x, y;	//像素位置
		COLORREF color;	//像素颜色
		StepPoint * next;
	}*pStepPoint,StepPoint;

	CPoint centerPoint;

private:
	


protected:
	
	int setPoint(StepPoint* point,int x, int y, COLORREF color);	//设置已经绘制点到链表里

public:
	
	pStepPoint getPoints();	//获取绘制的点链表
	void RotateObject();		//位移
	void ScaleObject();			//旋转
	void MoveObject();			//缩放
	void SetCenterPoint();	//设置图形中心点
	void GetCenterPoint();	//获取图形中心点
};

