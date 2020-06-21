// RotateDialog.cpp: 实现文件
//

#include "pch.h"
#include "MyCad.h"
#include "RotateDialog.h"
#include "afxdialogex.h"


// RotateDialog 对话框

IMPLEMENT_DYNAMIC(RotateDialog, CDialogEx)

RotateDialog::RotateDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

RotateDialog::~RotateDialog()
{
}

void RotateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RotateDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &RotateDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &RotateDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// RotateDialog 消息处理程序


void RotateDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	isRotate = true;
	CString str_Angle;
	CString str_Rotatex;
	CString str_Rotatey;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str_Angle);
	angle = _ttof(str_Angle);
	GetDlgItem(IDC_EDIT2)->GetWindowText(str_Rotatex);
	RotateX = _ttoi(str_Rotatex);
	GetDlgItem(IDC_EDIT3)->GetWindowText(str_Rotatey);
	RotateY = _ttoi(str_Rotatey);
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()==1) {
		isCenter = true;
	}
	else
		isCenter = false;
	CDialogEx::OnOK();
}


void RotateDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL RotateDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(1); //默认设置选中
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
