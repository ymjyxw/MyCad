#include "pch.h"
#include "JsonClass.h"

void JsonClass::ExportJsonFile()
{
	//TCHAR szFilter[] = _T("�ı��ļ�(*.json)|*.json||");
	//CFileDialog fileDlg(FALSE, _T("json"), _T("MyCad"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	//CString FileName;

	//// ��ʾ�����ļ��Ի���   
	//if (IDOK == fileDlg.DoModal())
	//{
	//	// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
	//	FileName = fileDlg.GetPathName();

	//}
	//else
	//	return;
	CString FileName = _T(".jsonfile.json");

	//���ڵ�
	Json::Value root;

	//���ڵ�����
	root["name"] = Json::Value("Mike Jiang");
	root["age"] = Json::Value(23);
	root["sex_is_male"] = Json::Value(true);

	//�ӽڵ�
	Json::Value partner;

	//�ӽڵ�����
	partner["partner_name"] = Json::Value("Galatea");
	partner["partner_age"] = Json::Value(21);
	partner["partner_sex_is_male"] = Json::Value(false);

	//�ӽڵ�ҵ����ڵ���
	root["partner"] = Json::Value(partner);

	//������ʽ
	root["achievement"].append("ach1");
	root["achievement"].append("ach2");
	root["achievement"].append("ach3");

	//ֱ�����
	cout << "FastWriter:" << endl;
	Json::FastWriter fw;
	cout << fw.write(root) << endl << endl;

	//�������
	cout << "StyledWriter:" << endl;
	Json::StyledWriter sw;
	cout << sw.write(root) << endl << endl;

	//������ļ�
	ofstream os;
	os.open(FileName);
	os << sw.write(root);
	os.close();
}
