// ScaleDialog.cpp: 实现文件
//

#include "pch.h"
#include "MyCad.h"
#include "ScaleDialog.h"
#include "afxdialogex.h"


// ScaleDialog 对话框

IMPLEMENT_DYNAMIC(ScaleDialog, CDialogEx)

ScaleDialog::ScaleDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

ScaleDialog::~ScaleDialog()
{
}

void ScaleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ScaleDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &ScaleDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ScaleDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// ScaleDialog 消息处理程序


void ScaleDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	IsScale = true;
	CString Scalex;
	CString Scaley;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Scalex);
	ScaleX = _ttof(Scalex);//x轴缩放
	GetDlgItem(IDC_EDIT2)->GetWindowText(Scaley);
	ScaleY = _ttof(Scaley);//y轴缩放

	CDialogEx::OnOK();
}


void ScaleDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
