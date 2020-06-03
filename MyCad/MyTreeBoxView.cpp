#include "pch.h"
#include "MyTreeBoxView.h"
#include "Resource.h"
BEGIN_MESSAGE_MAP(MyTreeBoxView, CDockablePane)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


void MyTreeBoxView::OnPaint()
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


void MyTreeBoxView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_treeDialog.SetWindowPos(this, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_treeDialog.ShowWindow(SW_SHOW);	//使得格子填满整个容器空间
}


int MyTreeBoxView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	// TODO:  在此添加您专用的创建代码
	if (!m_treeDialog.Create(IDD_TREEDIALOG, this))
	{
		TRACE0("未能设置参数设置");

		return -1;
	}
	m_treeDialog.ShowWindow(SW_SHOW);

	return 0;
}
