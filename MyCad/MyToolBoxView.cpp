#include "pch.h"
#include "MyToolBoxView.h"
#include "Resource.h"
BEGIN_MESSAGE_MAP(MyToolBoxView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()




int MyToolBoxView::OnCreate(LPCREATESTRUCT lpCreateStruct)	//����ڲ�Dialog
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	if (!m_toolDialog.Create(IDD_TOOLDIALOG, this))
	{
		TRACE0("δ�����ò�������");
		
		return -1;
	}
	m_toolDialog.ShowWindow(SW_SHOW);
	return 0;
}


void MyToolBoxView::OnSize(UINT nType, int cx, int cy)	//�����ƶ�ʱʹ�ô����ڲ��Ĵ��ڴ�С����Ӧ
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	m_toolDialog.SetWindowPos(this, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_toolDialog.ShowWindow(SW_SHOW);	//ʹ�ø����������������ռ�

}


void MyToolBoxView::OnPaint()	//�ػ洰�ڣ�ʹ�ô��ڱ���Ϊ��ɫ
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
