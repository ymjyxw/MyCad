#pragma once
#include<fstream>
#include <iostream>
#include<string>
#pragma comment(lib,"json_d.lib")
#include "json\json.h"
using namespace std;
class JsonClass
{
public:
	static void ExportJsonFile(CString path);	//±£´æjsonÎÄ¼þ
};

