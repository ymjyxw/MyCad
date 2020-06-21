#pragma once
#include "MyEdit.h"
class DrawBezier :
    public MyEdit
{
public:
	pStepPoint stepPoint = new StepPoint;

	int m_nCtrPs;//�����Ƶ���Ŀ��
	int	m_nSPs;	// ����������Ŀ��
	CPoint* m_pCtrPs; //�����Ƶ����꣩
	CPoint* m_curve;// ��ȫ�����������꣩

	
	int init();		//��ʼ������
	void setBezierPoint( int m, int x, int y);	//�������ߵ�m���Ƶ�����Ϊ��x��y��
	void computeCoefficients(int n, int* c); //����ϵ��, n Ϊ���Ƶ���Ŀ��c Ϊ�洢�ռ���׵�ַ���洢����Ϊϵ�� 
	void computePoint(float t, CPoint* pt, int nCtrPs, CPoint* pCtrPs, int* c); //���� Bezier �����ϲ���Ϊ t �ĵ�

	void Bezier(CPoint* pCtrPs, int nCtrPs, int m, CPoint* curve); //���� Bezier ���������в�����,m �������㣬��������� curve ��ָ���������� 



public:

	void DrawBezier::drawBezier(CPoint p1,CPoint p2,COLORREF color);
	int DrawBezier::setPoint(StepPoint* point, int x, int y, COLORREF color);//���õ�
	MyEdit::pStepPoint DrawBezier::getPoints();//��ȡ��

	
};

