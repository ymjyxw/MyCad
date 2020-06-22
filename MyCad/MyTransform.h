#pragma once
#include "pch.h"

class  MyTransform
{
	//ר�����ڴ���λ����ת���ŵ���

private:
	struct PointMatrix {	//�����
		int x;
		int y;
		int z;

	};

	typedef struct MyMatrix {	//3*3����
		float x1, x2, x3;
		float y1, y2, y3;
		float z1, z2, z3;
	}MATRIX;
public:

	static void InitTranslateMatrix(float x, float y, MATRIX * matrix);	//��ʼ��λ�ƾ���
	
	static void InitRotateMatrix(float angle, float x,float y, MATRIX* matrix);
	static void InitScaleMatrix(float x, float y, MATRIX* matrix);//��ʼ�����ž���

	static void InitMirrorMatrix(MATRIX* matrix, int direction);//��ʼ���������

	static void MatrixMultipy(PointMatrix* point, MATRIX* matrix);	//����˱任����


	static CPoint myglTranslatef(float x, float y, CPoint * point); //λ�ƺ���,����λ��ֵ��λ�Ƶ㣬����λ�Ƶ�
	static CPoint myglRotatef(float angle, float x, float y, CPoint* point);//��ת����,������ת���ĵ㣬λ��ֵ��λ�Ƶ㣬����λ�Ƶ�
	static CPoint myglScalef(float x, float y, CPoint cc, CPoint* point); //���ź���,��������x��y������λ�Ƶ�

	static CPoint myglMirrorf(CPoint cc,CPoint* point,int direction); //������,��������x��y������λ�Ƶ�



};

