
// MyCadView.cpp: CMyCadView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyCad.h"
#endif

#include "MyCadDoc.h"
#include "MyCadView.h"
#include "DrawLine.h"
#include "MainFrm.h"
#include "ToolDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyCadView

IMPLEMENT_DYNCREATE(CMyCadView, CView)

BEGIN_MESSAGE_MAP(CMyCadView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyCadView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMyCadView 构造/析构

CMyCadView::CMyCadView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMyCadView::~CMyCadView()
{
}

BOOL CMyCadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyCadView 绘图

void CMyCadView::OnDraw(CDC* pDC)
{
	CMyCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	DrawPoints(pDC);
}


// CMyCadView 打印


void CMyCadView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyCadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyCadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyCadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMyCadView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyCadView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CMyCadView::SetEditStepPoint(int step, int x, int y, COLORREF color)
{
	

}

void CMyCadView::DrawPoints(CDC *pDC)
{
	int i = 0;
	while (i < currentStep)
	{
		Points  *p = &(editStep[i].point);
		while (p)
		{
			pDC->SetPixel(p->x, p->y, p->color);
			p = p->next;
		}

		i++;
	}
}


// CMyCadView 诊断

#ifdef _DEBUG
void CMyCadView::AssertValid() const
{
	CView::AssertValid();
}

void CMyCadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyCadDoc* CMyCadView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyCadDoc)));
	return (CMyCadDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyCadView 消息处理程序


void CMyCadView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	

	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针
	if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWLINE)	//判断操作是否是画线
	{
		beginPoint = point;
	}

	CView::OnLButtonDown(nFlags, point);

}


void CMyCadView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针
	if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWLINE)	//判断操作是否是画线
	{
		
		endPoint = point;
		DrawLine MyDrawLine;
		MyDrawLine.DDALine(beginPoint.x, beginPoint.y, endPoint.x, endPoint.y,currentColor);	//获取点
		
		
		DrawLine::pStepPoint p = MyDrawLine.stepPoint;	//???获取MyDrawLine的像素点

		editStep[currentStep].step = currentStep;	//写入操作步骤
		Points* q = &(editStep[currentStep].point);	//获取表头结点
	

		while (p)	//写入像素点数据
		{
			q->x = p->x;
			q->y = p->y;
			q->color = p->color;
			Points* nq = new Points;
			nq->next = NULL;
			q->next = nq;
			q = q->next;
			p = p->next;
		}

		Invalidate();
			
		beginPoint = CPoint(0, 0);	//重置点
		endPoint = CPoint(0, 0);
		
		currentStep++;	//绘制步骤+1
	}
	CView::OnLButtonUp(nFlags, point);
}
