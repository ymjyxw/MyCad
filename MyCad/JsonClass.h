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
	static void ExportJsonFile(CString path);	//保存json文件
	static void OpenJsonFile(CString path); //打开json文件
};

