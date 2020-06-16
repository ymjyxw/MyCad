#include "pch.h"
#include "JsonClass.h"

void JsonClass::ExportJsonFile(CString path)
{



	//���ڵ�
	Json::Value root;

	//�ӽڵ�
	Json::Value step[1000];
	string str;
	CString cstr;
	int i = 0;
	while (i < 10)
	{
		//�ӽڵ�����
		step[i]["type"] = Json::Value("LINE");
		//������ʽ
		step[i]["Point_1"].append(1);
		step[i]["Point_1"].append(1);
		step[i]["Point_1"].append(1);

		step[i]["Point_2"].append(1);
		step[i]["Point_2"].append(1);
		step[i]["Point_2"].append(1);

		
		cstr.Format("%03d", i+1);
		str =  cstr.GetBuffer(0);

		//�ӽڵ�ҵ����ڵ���
		root["DrawStep_"+str] = Json::Value(step[i]);

		i++;
	}

	Json::StyledWriter sw;

	//������ļ�
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
