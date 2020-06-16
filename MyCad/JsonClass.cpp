#include "pch.h"
#include "JsonClass.h"

void JsonClass::SetJsonLineStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2)
{
	step[total_step]["type"] = Json::Value("LINE");

	//������ʽ

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

	//�ӽڵ�ҵ����ڵ���
	root["DrawStep_" + str] = Json::Value(step[total_step]);
	if(total_step<999)
		total_step++;
}

void JsonClass::SetJsonCircleStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2)
{
	step[total_step]["type"] = Json::Value("CIRCLE");

	//������ʽ

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

	//�ӽڵ�ҵ����ڵ���
	root["DrawStep_" + str] = Json::Value(step[total_step]);
	if (total_step < 999)
		total_step++;

}

void JsonClass::SetJsonRectStep(int cx, int cy, int x1, int y1, int r1, int g1, int b1, int x2, int y2, int r2, int g2, int b2)
{
	step[total_step]["type"] = Json::Value("RECT");

	//������ʽ

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

	//�ӽڵ�ҵ����ڵ���
	root["DrawStep_" + str] = Json::Value(step[total_step]);
	if (total_step < 999)
		total_step++;
}
void JsonClass::ExportJsonFile(CString path)
{


	Json::StyledWriter sw;

	//������ļ�
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

	if (dlg.DoModal() == IDOK)//��ʾ���ļ��Ի���
	{


		fileName = dlg.GetPathName();

		CFile openfile(fileName, CFile::modeRead);//����CFile����

		int length = openfile.GetLength();//��ȡ�ļ�����

		char* str;

		str = new char[length];

		openfile.Read(str, length);	//��ȡtxt�������������


		Json::Reader reader;

		Json::Value root;



		//���ַ����ж�ȡ����

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
