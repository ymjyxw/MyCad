#include "pch.h"
#include "JsonClass.h"

void JsonClass::ExportJsonFile(CString path)
{



	//���ڵ�
	Json::Value root;

	//�ӽڵ�
	Json::Value step[1000];
	string str;
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

		CString cstr;

		//�ӽڵ�ҵ����ڵ���
		cstr.Format("%03d", i+1);
		str =  cstr.GetBuffer(0);
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
