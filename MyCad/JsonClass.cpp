#include "pch.h"
#include "JsonClass.h"

void JsonClass::SetJsonLineStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2)
{
	step[total_step]["type"] = Json::Value("LINE");

	//数组形式

	step[total_step]["CenterPoint"].append(cx);
	step[total_step]["CenterPoint"].append(cy);
	

	step[total_step]["Point_1"].append(x1);
	step[total_step]["Point_1"].append(y1);
	step[total_step]["Point_1"].append(r1);
	step[total_step]["Point_1"].append(g1);
	step[total_step]["Point_1"].append(b1);
		
	step[total_step]["Point_2"].append(x2);
	step[total_step]["Point_2"].append(y2);
	step[total_step]["Point_2"].append(r2);
	step[total_step]["Point_2"].append(g2);
	step[total_step]["Point_2"].append(b2);

	string str;
	CString cstr;
	cstr.Format("%03d", total_step + 1);
	str = cstr.GetBuffer(0);

	//子节点挂到根节点上
	root["DrawStep_" + str] = Json::Value(step[total_step]);
	if(total_step<999)
		total_step++;
}

void JsonClass::SetJsonCircleStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2)
{
	step[total_step]["type"] = Json::Value("CIRCLE");

	//数组形式

	step[total_step]["CenterPoint"].append(cx);
	step[total_step]["CenterPoint"].append(cy);


	step[total_step]["Point_1"].append(x1);
	step[total_step]["Point_1"].append(y1);
	step[total_step]["Point_1"].append(r1);
	step[total_step]["Point_1"].append(g1);
	step[total_step]["Point_1"].append(b1);

	step[total_step]["Point_2"].append(x2);
	step[total_step]["Point_2"].append(y2);
	step[total_step]["Point_2"].append(r2);
	step[total_step]["Point_2"].append(g2);
	step[total_step]["Point_2"].append(b2);

	string str;
	CString cstr;
	cstr.Format("%03d", total_step + 1);
	str = cstr.GetBuffer(0);

	//子节点挂到根节点上
	root["DrawStep_" + str] = Json::Value(step[total_step]);
	if (total_step < 999)
		total_step++;

}

void JsonClass::SetJsonRectStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2)
{
	step[total_step]["type"] = Json::Value("RECT");

	//数组形式

	step[total_step]["CenterPoint"].append(cx);
	step[total_step]["CenterPoint"].append(cy);


	step[total_step]["Point_1"].append(x1);
	step[total_step]["Point_1"].append(y1);
	step[total_step]["Point_1"].append(r1);
	step[total_step]["Point_1"].append(g1);
	step[total_step]["Point_1"].append(b1);

	step[total_step]["Point_2"].append(x2);
	step[total_step]["Point_2"].append(y2);
	step[total_step]["Point_2"].append(r2);
	step[total_step]["Point_2"].append(g2);
	step[total_step]["Point_2"].append(b2);

	string str;
	CString cstr;
	cstr.Format("%03d", total_step + 1);
	str = cstr.GetBuffer(0);

	//子节点挂到根节点上
	root["DrawStep_" + str] = Json::Value(step[total_step]);
	if (total_step < 999)
		total_step++;
}
void JsonClass::ExportJsonFile(CString path)
{


	Json::StyledWriter sw;

	//输出到文件
	ofstream os;
	os.open(path);
	os << sw.write(root);
	os.close();
}

void JsonClass::OpenJsonFile()
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
