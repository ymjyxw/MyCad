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

void JsonClass::SetJsonFillRectStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2)
{
	step[total_step]["type"] = Json::Value("FILLRECT");

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

void JsonClass::SetJsonFillCircleStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2)
{
	step[total_step]["type"] = Json::Value("FILLCIRCLE");

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

void JsonClass::SetJsonBezierStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2)
{
	step[total_step]["type"] = Json::Value("BEZIER");

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

void JsonClass::SetJsonRoundCircleStep(int cx, int cy, int r, int g, int b, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	step[total_step]["type"] = Json::Value("ROUNDCIRCLE");

	//数组形式

	step[total_step]["CenterPoint"].append(cx);
	step[total_step]["CenterPoint"].append(cy);


	step[total_step]["Point_1"].append(x1);
	step[total_step]["Point_1"].append(y1);
	step[total_step]["Point_1"].append(r);
	step[total_step]["Point_1"].append(g);
	step[total_step]["Point_1"].append(b);

	step[total_step]["Point_2"].append(x2);
	step[total_step]["Point_2"].append(y2);
	step[total_step]["Point_2"].append(r);
	step[total_step]["Point_2"].append(g);
	step[total_step]["Point_2"].append(b);

	step[total_step]["Point_3"].append(x3);
	step[total_step]["Point_3"].append(y3);
	step[total_step]["Point_3"].append(r);
	step[total_step]["Point_3"].append(g);
	step[total_step]["Point_3"].append(b);


	step[total_step]["Point_4"].append(x4);
	step[total_step]["Point_4"].append(y4);
	step[total_step]["Point_4"].append(r);
	step[total_step]["Point_4"].append(g);
	step[total_step]["Point_4"].append(b);

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

		



		//从字符串中读取数据

		if (reader.parse(str, root))

		{
			
			

		}
		else
			AfxMessageBox(_T("READERROR"));
	}





}

int JsonClass::GetJsonCount()
{
	return root.size();
}

string JsonClass::GetJsonStepType(int step)
{
	if (step > 1000 || step < 1)	//输入不规范
		return "ERROR";
	string str;
	CString cstr;
	cstr.Format("%03d", step);
	str = cstr.GetBuffer(0);


	Json::Value root_current_step = root["DrawStep_"+str];
	
	string type = root_current_step["type"].asString();

	return type;
	
}

CPoint JsonClass::GetCenterPoint(int step)
{
	if (step > 1000 || step < 1)	//输入不规范
		return CPoint(0, 0);
	string str;
	CString cstr;
	cstr.Format("%03d", step);
	str = cstr.GetBuffer(0);


	Json::Value root_current_step = root["DrawStep_" + str];
	int cx = root_current_step["CenterPoint"][0].asInt();
	int cy = root_current_step["CenterPoint"][1].asInt();
	
	return CPoint(cx,cy);
}

CPoint JsonClass::GetPoint(int step, int num)
{
	if (step > 1000 || step < 1)	//输入不规范
		return CPoint(0,0);
	string str;
	CString cstr;
	cstr.Format("%03d", step);
	str = cstr.GetBuffer(0);
	Json::Value root_current_step = root["DrawStep_" + str];
	
	string str_num;
	str_num = "Point_" + std::to_string(num);

	int x = root_current_step[str_num][0].asInt();
	int y = root_current_step[str_num][1].asInt();

	return CPoint(x, y);

}

COLORREF JsonClass::GetColor(int step, int num)
{
	if (step > 1000 || step < 1)	//输入不规范
		return RGB(0,0,0);
	string str;
	CString cstr;
	cstr.Format("%03d", step);
	str = cstr.GetBuffer(0);
	Json::Value root_current_step = root["DrawStep_" + str];

	string str_num;
	str_num = "Point_" + std::to_string(num);

	int r = root_current_step[str_num][2].asInt();
	int g = root_current_step[str_num][3].asInt();
	int b = root_current_step[str_num][4].asInt();

	
	return RGB(r, g, b);
}
