#pragma once


class MyEdit
{
public :
	typedef struct StepPoint	//���ص�����
	{	
		int x, y;	//����λ��
		COLORREF color;	//������ɫ
		StepPoint * next;
	}*pStepPoint,StepPoint;


private:
	


protected:
	
	int setPoint(StepPoint* point,int x, int y, COLORREF color);	//�����Ѿ����Ƶ㵽������

public:
	
	pStepPoint getPoints();	//��ȡ���Ƶĵ�����
	

};

