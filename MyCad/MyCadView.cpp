
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
#include "MyTransform.h"

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
//	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
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


void CMyCadView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


void CMyCadView::DrawPoints(CDC *pDC)
{
	int i = 0;
	while (i < currentStep)
	{
		Points  *p = &(stepPoints[i].point);
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


void CMyCadView::SetTreeDialog(int num, CString str)
{
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针

	CString str_num;
	str_num.Format(_T("%d"), num);
	str = str_num + _T("——") + str;

	pMainFrame->m_treeBoxView.m_treeDialog.SetTreeItem(str);


}

void CMyCadView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	

	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针
	if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWLINE)	//判断操作是否是画线
	{
		beginPoint = point;
	}
	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::MOVEOBJECT)	//移动事件
	{
		beginTransform = true;
	}

	CView::OnLButtonDown(nFlags, point);

}


void CMyCadView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针
	if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWLINE)	//判断操作是否是画线
	{
		COLORREF color = pMainFrame->m_toolBoxView.m_toolDialog.currentColor;	//获取颜色
		endPoint = point;
		while (endPoint == beginPoint)	//起点终点想同，退出
		{
			return;
		}
		
		this->SetLine(beginPoint, endPoint, color,currentStep);

		Invalidate();

		beginPoint = CPoint(0, 0);	//重置点
		endPoint = CPoint(0, 0);
		
		currentStep++;	//绘制步骤+1
		
		this->SetTreeDialog(currentStep,_T("绘制直线"));

	}
	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::MOVEOBJECT)	//移动事件
	{
		beginTransform = false;
	}

	CView::OnLButtonUp(nFlags, point);
}


void CMyCadView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针
	if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::MOVEOBJECT && beginTransform)	//移动事件
	{
		
		//当前只修改这一步骤下的图形
		int select = pMainFrame->m_treeBoxView.m_treeDialog.tree_currentStep;	//获取选中的图形
		if (select < 0)	//没有选中图形，直接退出
		{

			MessageBox(_T("没有选择图形"));
			return;
		}
					

	
		
		if (editSteps[select].type == LINE)	//移动的对象是线条
		{
			COLORREF color = editSteps[select].point.color;	//获取颜色
			CPoint p1 = CPoint(editSteps[select].point.x, editSteps[select].point.y);	//获取关键点
			CPoint p2 = CPoint(editSteps[select].point.next->x, editSteps[select].point.next->y);


			//p1 += (point - editSteps[currentStep].centerPoint);//获取移动后的点
			//p2 += (point - editSteps[currentStep].centerPoint);

			int dx = point.x - editSteps[select].centerPoint.x;	//获取位移量
			int dy = point.y - editSteps[select].centerPoint.y;

			p1 = MyTransform::myglTranslatef(dx, dy, &p1);	//位移关键点
			p2 = MyTransform::myglTranslatef(dx, dy, &p2);
				
			this->SetLine(p1, p2, color,select);	//重新绘制

		}


		Invalidate();
		

	}
	CView::OnMouseMove(nFlags, point);
}


void CMyCadView::SetLine(CPoint p1, CPoint p2, COLORREF color, int s )
{
	DrawLine MyDrawLine;
	MyDrawLine.DDALine(p1.x, p1.y, p2.x, p2.y, color);	//获取点

	DrawLine::pStepPoint p = MyDrawLine.stepPoint;	//获取MyDrawLine的像素点
	stepPoints[s].step = s;	//写入操作步骤
	Points* q = &(stepPoints[s].point);	//获取表头结点



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


	//保存操作记录
	editSteps[s].type = LINE; //绘制的是线条
	editSteps[s].centerPoint = CPoint((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);//中心点
	editSteps[s].point.x = p1.x;	//写入关键点数据
	editSteps[s].point.y = p1.y;
	editSteps[s].point.color = color;
	Points *newPoint = new Points;
	editSteps[s].point.next = newPoint;
	newPoint->x = p2.x;	//写入关键点数据
	newPoint->y = p2.y;
	newPoint->color = color;
	newPoint->next = NULL;


}

void CMyCadView::GetcurrentEditStep()
{
}
