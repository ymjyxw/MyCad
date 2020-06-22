#include "pch.h"
#include "MyTransform.h"

CPoint MyTransform::myglTranslatef(float x, float y, CPoint * point)
{
	
	PointMatrix P;
	P.x = point->x;
	P.y = point->y;
	P.z = 1;

	MATRIX *translate_matrix = new MATRIX;
	InitTranslateMatrix(x, y, translate_matrix);
	MatrixMultipy(&P, translate_matrix);

	return CPoint(P.x, P.y);
}


CPoint MyTransform::myglRotatef(float angle, float x, float y, CPoint* point)
{
	PointMatrix P;
	P.x = point->x;
	P.y = point->y;
	P.z = 1;


	MATRIX* rotate_matrix = new MATRIX;
	InitRotateMatrix(angle, x, y, rotate_matrix);
	MatrixMultipy(&P, rotate_matrix);

	return CPoint(P.x, P.y);
}

void MyTransform::InitTranslateMatrix(float x, float y, MATRIX * matrix)
{
	matrix->x2 = matrix->x3 = matrix->y1 = matrix->y3 = 0;
	matrix->x1 = matrix->y2 = matrix->z3 = 1;
	matrix->z1 = x;
	matrix->z2 = y;

}

void MyTransform::MatrixMultipy(PointMatrix * point, MATRIX * matrix)
{
	int x, y, z;
	x = point->x;
	y = point->y;
	z = point->z;

	point->x = int(x*matrix->x1 + y * matrix->y1 + z * matrix->z1 + 0.5);
	point->y = int(x*matrix->x2 + y * matrix->y2 + z * matrix->z2 + 0.5);
	point->z = int(x*matrix->x3 + y * matrix->y3 + z * matrix->z3 + 0.5);

}

void MyTransform::InitRotateMatrix(float angle, float x, float y, MATRIX* matrix)
{

	matrix->x1 = cos(angle);
	matrix->y2 = cos(angle);
	matrix->x2 = sin(angle);
	matrix->y1 = (-1) * sin(angle);
	matrix->x3 = matrix->y3 = 0;
	matrix->z1 = x - x * cos(angle) + y * sin(angle);
	matrix->z2 = y - x * sin(angle) - y * cos(angle);
	matrix->z3 = 1;


}


void MyTransform::InitScaleMatrix(float x, float y, MATRIX* matrix)
{
	matrix->x1 = x;
	matrix->y2 = y;
	matrix->x2 = matrix->y1 = matrix->x3 = matrix->y3 = matrix->z1 = matrix->z2 = 0;
	matrix->z3 = 1;
}

void MyTransform::InitMirrorMatrix( MATRIX* matrix, int direction)
{
	if (direction == 1)
	{
		matrix->x1 = 1;
		matrix->y2 = -1;
		matrix->x2 = matrix->y1 = matrix->x3 = matrix->y3 = matrix->z1 = matrix->z2 = 0;
		matrix->z3 = 1;
	}
	else if (direction == 2)
	{
		matrix->x1 = -1;
		matrix->y2 = 1;
		matrix->x2 = matrix->y1 = matrix->x3 = matrix->y3 = matrix->z1 = matrix->z2 = 0;
		matrix->z3 = 1;
	}
	else
	{
		matrix->x1 = -1;
		matrix->y2 = -1;
		matrix->x2 = matrix->y1 = matrix->x3 = matrix->y3 = matrix->z1 = matrix->z2 = 0;
		matrix->z3 = 1;
	}
}



CPoint MyTransform::myglScalef(float x, float y, CPoint cc, CPoint* point)
{
	PointMatrix P;
	P.x = point->x;
	P.y = point->y;
	P.z = 1;

	/*float dx = point->x;
	float dy = point->y;*/

	//先位移至坐标原点
	MATRIX* translate_matrix1 = new MATRIX;
	InitTranslateMatrix(-1 * cc.x, -1 * cc.y, translate_matrix1);
	MatrixMultipy(&P, translate_matrix1);

	MATRIX* scale_matrix = new MATRIX;
	InitScaleMatrix(x, y, scale_matrix);
	MatrixMultipy(&P, scale_matrix);

	//P.x = P.x * cc.x + x * (1 - cc.x);
	//P.y = P.y * cc.y + y * (1 - cc.y);

	MATRIX* translate_matrix2 = new MATRIX;
	InitTranslateMatrix(cc.x, cc.y, translate_matrix2);
	MatrixMultipy(&P, translate_matrix2);




	return CPoint(P.x, P.y);
}

CPoint MyTransform::myglMirrorf(CPoint cc,CPoint* point, int direction)
{
	PointMatrix P;
	P.x = point->x;
	P.y = point->y;
	P.z = 1;

	MATRIX* translate_matrix1 = new MATRIX;
	InitTranslateMatrix(-1 * cc.x, -1 * cc.y, translate_matrix1);
	MatrixMultipy(&P, translate_matrix1);

	MATRIX* mirror_matrix = new MATRIX;
	InitMirrorMatrix(mirror_matrix, direction);
	MatrixMultipy(&P, mirror_matrix);

	MATRIX* translate_matrix2 = new MATRIX;
	InitTranslateMatrix(cc.x, cc.y, translate_matrix2);
	MatrixMultipy(&P, translate_matrix2);

	return CPoint(P.x,P.y);
}
