#pragma once
#include<fstream>
#include <iostream>
#include<string>
#pragma comment(lib,"json_d.lib")
#include "json\json.h"
#include <conio.h>
using namespace std;
class JsonClass
{
public:

	//���ڵ�
	Json::Value root;

	//�ӽڵ�
	Json::Value step[1000];

	int total_step = 0;

	void SetJsonLineStep(int cx,int cy,int x1, int y1, int r1,int g1,int b1, int x2,int y2,int r2,int g2,int b2);	//д��json����
	void SetJsonCircleStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2);	//д��json����
	void SetJsonRectStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2);	//д��json����
	void SetJsonFillRectStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2);	//д��json����
	void SetJsonFillCircleStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2);	//д��json����
	void SetJsonBezierStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2);	//д��json����
	void SetJsonRoundCircleStep(int cx, int cy, int r, int g, int b, int x1, int y1, int x2, int y2, int x3, int y3, int x4,int y4);
	void ExportJsonFile(CString path);	//����json�ļ�
	void OpenJsonFile(); //��json�ļ�
	
	int GetJsonCount();	//��ȡ��ǰjson root�µ���Ŀ

	string GetJsonStepType(int step);// ��ȡ��step������
	CPoint GetCenterPoint(int step);	//��ȡ���ĵ�
	CPoint GetPoint(int step, int num); //��ȡ��step���ĵ�num���ؼ���
	COLORREF GetColor(int step, int num); //��ȡ��step���ĵ�num���ؼ�����ɫ
};

