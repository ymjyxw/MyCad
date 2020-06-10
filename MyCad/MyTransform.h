#pragma once
#include "pch.h"
class  MyTransform
{
	//专门用于处理位移旋转缩放的类

private:
	struct PointMatrix {	//点矩阵
		int x;
		int y;
		int z;

	};

	typedef struct MyMatrix {	//3*3矩阵
		float x1, x2, x3;
		float y1, y2, y3;
		float z1, z2, z3;
	}MATRIX;

	static void InitTranslateMatrix(float x, float y, MATRIX * matrix);	//初始化位移矩阵
	static void MatrixMultipy(PointMatrix * point, MATRIX * matrix);	//矩阵乘变换矩阵

public:
	static CPoint myglTranslatef(float x, float y, CPoint * point); //位移函数,传入位移值与位移点，返回位移点

};

