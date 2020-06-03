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
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDockablePane::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	dc.FillRect(&rect, &brush);
}


void MyTreeBoxView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	m_treeDialog.SetWindowPos(this, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_treeDialog.ShowWindow(SW_SHOW);	//ʹ�ø����������������ռ�
}


int MyTreeBoxView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	// TODO:  �ڴ������ר�õĴ�������
	if (!m_treeDialog.Create(IDD_TREEDIALOG, this))
	{
		TRACE0("δ�����ò�������");

		return -1;
	}
	m_treeDialog.ShowWindow(SW_SHOW);

	return 0;
}
