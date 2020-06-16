#include "pch.h"
#include "JsonClass.h"

void JsonClass::ExportJsonFile()
{
	//TCHAR szFilter[] = _T("文本文件(*.json)|*.json||");
	//CFileDialog fileDlg(FALSE, _T("json"), _T("MyCad"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	//CString FileName;

	//// 显示保存文件对话框   
	//if (IDOK == fileDlg.DoModal())
	//{
	//	// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
	//	FileName = fileDlg.GetPathName();

	//}
	//else
	//	return;
	CString FileName = _T(".jsonfile.json");

	//根节点
	Json::Value root;

	//根节点属性
	root["name"] = Json::Value("Mike Jiang");
	root["age"] = Json::Value(23);
	root["sex_is_male"] = Json::Value(true);

	//子节点
	Json::Value partner;

	//子节点属性
	partner["partner_name"] = Json::Value("Galatea");
	partner["partner_age"] = Json::Value(21);
	partner["partner_sex_is_male"] = Json::Value(false);

	//子节点挂到根节点上
	root["partner"] = Json::Value(partner);

	//数组形式
	root["achievement"].append("ach1");
	root["achievement"].append("ach2");
	root["achievement"].append("ach3");

	//直接输出
	cout << "FastWriter:" << endl;
	Json::FastWriter fw;
	cout << fw.write(root) << endl << endl;

	//缩进输出
	cout << "StyledWriter:" << endl;
	Json::StyledWriter sw;
	cout << sw.write(root) << endl << endl;

	//输出到文件
	ofstream os;
	os.open(FileName);
	os << sw.write(root);
	os.close();
}
