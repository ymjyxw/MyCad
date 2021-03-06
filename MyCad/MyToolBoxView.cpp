#include "pch.h"
#include "MyToolBoxView.h"
#include "Resource.h"
BEGIN_MESSAGE_MAP(MyToolBoxView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()




int MyToolBoxView::OnCreate(LPCREATESTRUCT lpCreateStruct)	//添加内部Dialog
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (!m_toolDialog.Create(IDD_TOOLDIALOG, this))
	{
		TRACE0("未能设置参数设置");
		
		return -1;
	}
	m_toolDialog.ShowWindow(SW_SHOW);
	return 0;
}


void MyToolBoxView::OnSize(UINT nType, int cx, int cy)	//窗口移动时使得窗口内部的窗口大小自适应
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	m_toolDialog.SetWindowPos(this, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_toolDialog.ShowWindow(SW_SHOW);	//使得格子填满整个容器空间

}


void MyToolBoxView::OnPaint()	//重绘窗口，使得窗口背景为白色
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDockablePane::OnPaint()

	CRect rect;
	GetClientRect(&rect);
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	dc.FillRect(&rect, &brush);
}
