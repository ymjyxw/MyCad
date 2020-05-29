// ToolDialog.cpp: 实现文件
//

#include "pch.h"
#include "MyCad.h"
#include "ToolDialog.h"
#include "afxdialogex.h"


// ToolDialog 对话框

IMPLEMENT_DYNAMIC(ToolDialog, CDialogEx)

ToolDialog::ToolDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOOLDIALOG, pParent)
{

}

ToolDialog::~ToolDialog()
{
}

void ToolDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ToolDialog, CDialogEx)
END_MESSAGE_MAP()


// ToolDialog 消息处理程序
