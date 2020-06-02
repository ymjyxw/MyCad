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
