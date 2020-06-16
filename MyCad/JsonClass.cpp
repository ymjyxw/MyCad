#include "pch.h"
#include "JsonClass.h"

void JsonClass::ExportJsonFile(CString path)
{



	//根节点
	Json::Value root;

	//子节点
	Json::Value step[1000];
	string str;
	CString cstr;
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

		
		cstr.Format("%03d", i+1);
		str =  cstr.GetBuffer(0);

		//子节点挂到根节点上
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

void JsonClass::OpenJsonFile(CString path)
{
	CString strFilter, fileName;

	strFilter = "json Files(*.json)|*.json||";

	CFileDialog dlg(TRUE, NULL, NULL, OFN_EXPLORER | OFN_HIDEREADONLY | OFN_ENABLESIZING | OFN_FILEMUSTEXIST, strFilter);

	if (dlg.DoModal() == IDOK)//显示打开文件对话框
	{


		fileName = dlg.GetPathName();

		CFile openfile(fileName, CFile::modeRead);//构造CFile对象

		int length = openfile.GetLength();//获取文件长度

		char* str;

		str = new char[length];

		openfile.Read(str, length);	//读取txt里面的所有数据


		Json::Reader reader;

		Json::Value root;



		//从字符串中读取数据

		if (reader.parse(str, root))

		{
			Json::Value root_1 = root["DrawStep001"];
			string t = root_1["type"].asString();
		
			
			if (t.compare("LINE"))
			{
				AfxMessageBox(_T("equal"));
			}
			else
				AfxMessageBox(_T("no_equal"));
			

		}
		else
			AfxMessageBox(_T("READERROR"));
	}





}
