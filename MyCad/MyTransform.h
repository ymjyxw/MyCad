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

	static void InitTranslateMatrix(float x, float y, MATRIX * matrix);	//��ʼ��λ�ƾ���
	static void MatrixMultipy(PointMatrix * point, MATRIX * matrix);	//����˱任����

public:
	static CPoint myglTranslatef(float x, float y, CPoint * point); //λ�ƺ���,����λ��ֵ��λ�Ƶ㣬����λ�Ƶ�

};

