#include "pch.h"
#include "JsonClass.h"

void JsonClass::ExportJsonFile(CString path)
{



	//根节点
	Json::Value root;

	//子节点
	Json::Value step[1000];
	string str;
	int i = 0;
	while (i < 10)
	{
		//子节点属性
		step[i]["type"] = Json::Value("LINE");
		//数组形式
		step[i]["Point_1"].append(1);
		step[i]["Point_1"].append(1);
		step[i]["Point_1"].append(1);

		step[i]["Point_2"].append(1);
		step[i]["Point_2"].append(1);
		step[i]["Point_2"].append(1);

		CString cstr;

		//子节点挂到根节点上
		cstr.Format("%03d", i+1);
		str =  cstr.GetBuffer(0);
		root["DrawStep_"+str] = Json::Value(step[i]);

		i++;
	}

	Json::StyledWriter sw;

	//输出到文件
	ofstream os;
	os.open(path);
	os << sw.write(root);
	os.close();
}
