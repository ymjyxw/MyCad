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
	void ExportJsonFile(CString path);	//����json�ļ�
	void OpenJsonFile(); //��json�ļ�
	
};

