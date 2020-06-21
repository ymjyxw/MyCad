// ToolDialog.cpp: 实现文件
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
	ON_BN_CLICKED(IDC_BUTTON7, &ToolDialog::OnSetColor)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON8, &ToolDialog::OnDrawFillCircle)
	ON_BN_CLICKED(IDC_BUTTON9, &ToolDialog::OnDrawBezier)
	ON_BN_CLICKED(IDC_BUTTON11, &ToolDialog::OnDrawYuanHu)
END_MESSAGE_MAP()


// ToolDialog 消息处理程序



void ToolDialog::OnDrawLine()	//点击画线按钮，实现画线功能
{
	// TODO: 在此添加控件通知处理程序代码
	currentModel = DRAWLINE;
	
}




void ToolDialog::OnDrawCircle()
{
	// TODO: 在此添加控件通知处理程序代码
	currentModel = DRAWCIRCLE;
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

void ToolDialog::OnMoveObject()
{
	// TODO: 在此添加控件通知处理程序代码
	//普通类获取view类指针

	currentModel = MOVEOBJECT;

	CMainFrame* p = (CMainFrame*)AfxGetApp()->m_pMainWnd;	//获取框架指针
	CMyCadView* pv = (CMyCadView*)p->GetActiveView();	//获取view指针

	pv->Invalidate();
}




void ToolDialog::OnRotateObject()
{
	// TODO: 在此添加控件通知处理程序代码
	currentModel = ROTATEOBJECT;

	CMainFrame* p = (CMainFrame*)AfxGetApp()->m_pMainWnd;	//获取框架指针
	CMyCadView* pv = (CMyCadView*)p->GetActiveView();	//获取view指针

	pv->RotateObject();
}

void ToolDialog::OnSetColor()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CColorDialog cd;

	if (cd.DoModal() == IDOK)
	{
		//获取选中的颜色
		currentColor = cd.GetColor();
		CRect rct;
		CWnd* pic = GetDlgItem(IDC_PIC);
		CDC* pDC = pic->GetDC();
		pic->GetWindowRect(&rct);
		CBrush brs;
		brs.CreateSolidBrush(currentColor);
		CRect picrct;
		picrct.top = 0;
		picrct.left = 0;
		picrct.bottom = rct.Height() / 1.08f;
		picrct.right = rct.Width() / 1.08f;
		pDC->FillRect(&picrct, &brs);
	}
	
}


void ToolDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	//设置pic_control初始颜色
	UpdateData(TRUE);//将控件的数据更新到与之关联的空间变量
	CRect rct;
	GetDlgItem(IDC_PIC)->GetWindowRect(&rct);//得到示例的画图区域
	ScreenToClient(&rct);
	CBrush brs;
	brs.CreateSolidBrush(currentColor);
	dc.FillRect(rct, &brs);




}


void ToolDialog::OnDrawFillCircle()
{
	// TODO: 在此添加控件通知处理程序代码
	currentModel = DRAWFILLCIRCLE;
}


void ToolDialog::OnDrawBezier()
{
	// TODO: 在此添加控件通知处理程序代码
	currentModel = DRAWBEZIER;

}


void ToolDialog::OnDrawYuanHu()
{
	// TODO: 在此添加控件通知处理程序代码
	currentModel = DRAWYUANHU;
}
