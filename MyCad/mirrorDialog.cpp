// mirrorDialog.cpp: 实现文件
//

#include "pch.h"
#include "MyCad.h"
#include "mirrorDialog.h"
#include "afxdialogex.h"


// mirrorDialog 对话框

IMPLEMENT_DYNAMIC(mirrorDialog, CDialogEx)

mirrorDialog::mirrorDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

mirrorDialog::~mirrorDialog()
{
}

void mirrorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(mirrorDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &mirrorDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &mirrorDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO1, &mirrorDialog::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &mirrorDialog::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &mirrorDialog::OnBnClickedRadio3)
END_MESSAGE_MAP()


// mirrorDialog 消息处理程序


void mirrorDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	isMirror = true;
	CDialogEx::OnOK();
}


void mirrorDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void mirrorDialog::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	direction = 1;
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
}


void mirrorDialog::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	direction = 2;
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
}


void mirrorDialog::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	direction = 3;
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
}


BOOL mirrorDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
