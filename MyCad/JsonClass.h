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

	//根节点
	Json::Value root;

	//子节点
	Json::Value step[1000];

	int total_step = 0;

	void SetJsonLineStep(int cx,int cy,int x1, int y1, int r1,int g1,int b1, int x2,int y2,int r2,int g2,int b2);	//写入json数据
	void SetJsonCircleStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2);	//写入json数据
	void SetJsonRectStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2);	//写入json数据
	void SetJsonFillRectStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2);	//写入json数据
	void SetJsonFillCircleStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2);	//写入json数据
	void SetJsonBezierStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2);	//写入json数据
	void SetJsonRoundCircleStep(int cx, int cy, int r, int g, int b, int x1, int y1, int x2, int y2, int x3, int y3, int x4,int y4);
	void ExportJsonFile(CString path);	//保存json文件
	void OpenJsonFile(); //打开json文件
	
	int GetJsonCount();	//获取当前json root下的数目

	string GetJsonStepType(int step);// 获取第step的类型
	CPoint GetCenterPoint(int step);	//获取中心点
	CPoint GetPoint(int step, int num); //获取第step步的第num个关键点
	COLORREF GetColor(int step, int num); //获取第step步的第num个关键点颜色
};

