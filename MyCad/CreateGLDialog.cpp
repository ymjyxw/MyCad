// CreateGLDialog.cpp: 实现文件
//

#include "pch.h"
#include "MyCad.h"
#include "CreateGLDialog.h"
#include "afxdialogex.h"


// CreateGLDialog 对话框

IMPLEMENT_DYNAMIC(CreateGLDialog, CDialogEx)

CreateGLDialog::CreateGLDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CreateGLDialog::~CreateGLDialog()
{
}

void CreateGLDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPENGL, Open_Pic);
}


BEGIN_MESSAGE_MAP(CreateGLDialog, CDialogEx)
END_MESSAGE_MAP()


// CreateGLDialog 消息处理程序


BOOL CreateGLDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;

	//获取照片控制器位置
	//GetDlgItem(IDC_OPENGL)->GetWindowRect(rect);
	Open_Pic.GetWindowRect(rect);

	//转换为屏幕坐标
	ScreenToClient(rect);

	// 创建OPenGL窗口
	//m_oglWindow.oglCreate(rect, this);

	// 设置OpenGL窗口渲染时间
	//m_oglWindow.m_unpTimer = m_oglWindow.SetTimer(1, 1, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
