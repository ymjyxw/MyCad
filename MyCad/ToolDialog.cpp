﻿// ToolDialog.cpp: 实现文件
//

#include "pch.h"
#include "MyCad.h"
#include "ToolDialog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MyCadView.h"
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
	
	ON_BN_CLICKED(IDC_BUTTON1, &ToolDialog::OnDrawLine)
	ON_BN_CLICKED(IDC_BUTTON2, &ToolDialog::OnMoveObject)
	ON_BN_CLICKED(IDC_BUTTON3, &ToolDialog::OnDrawCircle)
	ON_BN_CLICKED(IDC_BUTTON4, &ToolDialog::OnRotateObject)
	ON_BN_CLICKED(IDC_BUTTON5, &ToolDialog::OnDrawRect)

	ON_BN_CLICKED(IDC_BUTTON6, &ToolDialog::OnCreateFillRect)
END_MESSAGE_MAP()


// ToolDialog 消息处理程序



void ToolDialog::OnDrawLine()	//点击画线按钮，实现画线功能
{
	// TODO: 在此添加控件通知处理程序代码
	currentModel = DRAWLINE;
	
}


void ToolDialog::OnMoveObject()
{
	// TODO: 在此添加控件通知处理程序代码
	//普通类获取view类指针
	
	currentModel = MOVEOBJECT;

	CMainFrame* p = (CMainFrame*)AfxGetApp()->m_pMainWnd;	//获取框架指针
	CMyCadView* pv = (CMyCadView*)p->GetActiveView();	//获取view指针

	pv->Invalidate(); 
}


void ToolDialog::OnDrawCircle()
{
	// TODO: 在此添加控件通知处理程序代码
	currentModel = DRAWCIRCLE;
}


void ToolDialog::OnRotateObject()
{
	// TODO: 在此添加控件通知处理程序代码
	currentModel = ROTATEOBJECT;
}


void ToolDialog::OnDrawRect()
{
	// TODO: 在此添加控件通知处理程序代码
	currentModel = DRAWRECT;
}



void ToolDialog::OnCreateFillRect()
{
	// TODO: 在此添加控件通知处理程序代码
	currentModel = DRAWFILLRECT;
}
