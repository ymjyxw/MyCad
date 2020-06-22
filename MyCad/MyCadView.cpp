
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
#include "DrawRect.h"
#include "DrawCircle.h"
#include "DrawFillRect.h"
#include "DrawFillCircle.h"
#include "DrawBezier.h"
#include "MainFrm.h"
#include "ToolDialog.h"
#include "MyTransform.h"
#include "JsonClass.h"
#include "CreateGLDialog.h"
#include "RotateDialog.h"
#include "ScaleDialog.h"
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
	ON_COMMAND(ID_32775, &CMyCadView::OnExportImage)
//	ON_WM_KEYDOWN()

//ON_WM_TIMER()

ON_COMMAND(ID_FILE_NEW, &CMyCadView::OnFileNew)
ON_COMMAND(ID_FILE_SAVE, &CMyCadView::OnFileSave)
ON_COMMAND(ID_FILE_OPEN, &CMyCadView::OnFileOpen)
ON_WM_TIMER()
ON_COMMAND(ID_32777, &CMyCadView::OnExportVideo)
ON_COMMAND(ID_32778, &CMyCadView::OnShowGLDialog)
END_MESSAGE_MAP()

// CMyCadView 构造/析构

CMyCadView::CMyCadView() noexcept
{
	// TODO: 在此处添加构造代码
	AllocConsole();//打开控制台
	
}

CMyCadView::~CMyCadView()
{
	
	FreeConsole();//释放控制台资源
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

	if (is_create_video)
		return;

	//蜜汁双缓存
	CDC MemDC; //首先定义一个显示设备对象
	CBitmap MemBitmap;//定义一个位图对象
	//随后建立与屏幕显示兼容的内存显示设备
	MemDC.CreateCompatibleDC(NULL);
	//这时还不能绘图，因为没有地方画 ^_^
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
	CRect  rcClient;
	GetClientRect(&rcClient);
	MemBitmap.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());
	//将位图选入到内存显示设备中
	//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
	CBitmap* pOldBit = MemDC.SelectObject(&MemBitmap);
	//先用背景色将位图清除干净，这里我用的是白色作为背景
	//你也可以用自己应该用的颜色
	MemDC.FillSolidRect(0, 0, rcClient.Width(), rcClient.Height(),
		RGB(255, 255, 255));       //绘图
	DrawPoints(&MemDC);
	//将内存中的图拷贝到屏幕上进行显示
	pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(),
		&MemDC, 0, 0, SRCCOPY);       //绘图完成后的清理
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
	
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	
	if(currentEditStep>=0 && pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::MOVEOBJECT)	//高亮图形
		HighObject(currentEditStep);


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

// 绘制所有的点
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

//设置树状图 num - 绘制步骤 str - 绘制操作
void CMyCadView::SetTreeDialog(int num, CString str)
{
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针

	CString str_num;
	str_num.Format(_T("%d"), num);
	str = str_num + _T("——") + str;

	pMainFrame->m_treeBoxView.m_treeDialog.SetTreeItem(str);


}

//高亮图形
void CMyCadView::HighObject(int step)
{
	
	//CDC * pDC = GetDC();//初始化指针pDC
	//
	CPoint cp = editSteps[step].centerPoint;
	//CPoint ld = cp - CPoint(10, 10);
	//CPoint rt = cp + CPoint(10, 10);

	//CBrush NewBrush, *pOldBrush;
	//NewBrush.CreateSolidBrush(RGB(255, 0, 0));
	//pOldBrush = pDC->SelectObject(&NewBrush);
	//pDC->Ellipse(CRect(ld, rt));
	//pDC->MoveTo(cp);

	//pDC->LineTo(CPoint(cp.x + 20, cp.y));

	//pDC->SelectObject(pOldBrush);
	//NewBrush.DeleteObject();
	//ReleaseDC(pDC);//释放指针
	CImage* m_pImgBk = new CImage;
	m_pImgBk->Load(_T("res\\zuobiaozhou.png"));
	if (m_pImgBk->IsNull()) // 图片加载失败
	{
		delete m_pImgBk;
		m_pImgBk = NULL;
		return;
	}
	if (m_pImgBk->GetBPP() == 32)
	{
		for (int i = 0; i < m_pImgBk->GetWidth(); i++)
		{
			for (int j = 0; j < m_pImgBk->GetHeight(); j++)
			{
				unsigned char* pucColor = reinterpret_cast<unsigned char*>(m_pImgBk->GetPixelAddress(i, j));
				pucColor[0] = pucColor[0] * pucColor[3] / 255;
				pucColor[1] = pucColor[1] * pucColor[3] / 255;
				pucColor[2] = pucColor[2] * pucColor[3] / 255;
			}
		}
	}
	CWindowDC dc(this);
	if (m_pImgBk != NULL)
	{
		int nDstWidth = 143;
		int nDstHeight = 231;
		m_pImgBk->Draw(dc.GetSafeHdc(), cp.x-7, cp.y-154, nDstWidth, nDstHeight);
	}
}



void CMyCadView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	

	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针
	if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel != ToolDialog::DRAWYUANHU) //圆弧初始化
	{
		twop = 0;
		ing = 0;
		beginPoint2 = (0, 0);
		beginPoint3 = (0, 0);
	}

	if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWLINE)	//判断操作是否是画线
	{
		beginPoint = point;
		currentEditStep = -1;
	}
	if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWCIRCLE)	//判断操作是否是画线
	{
		beginPoint = point;
		currentEditStep = -1;
	}
	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::MOVEOBJECT)	//移动事件
	{
		beginTransform = true;
		
		
	}

	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWRECT)	//画矩形事件
	{
		beginPoint = point;
	}
	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWFILLRECT) //画实心矩形
	{
		beginPoint = point;
	}
	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWFILLCIRCLE) //画实心圆形
	{
		beginPoint = point;
	}
	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWBEZIER) //画贝塞尔
	{
		beginPoint = point;
	}
	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWYUANHU) //画圆弧
	{

		if (twop == 0)
		{
			beginPoint = point;
		
		}
		if (twop == 1)
			beginPoint2 = point;
		if (twop == 2)
		{
			beginPoint3 = point;
			currentStep++;
		}
			
		if (twop > 1)
			ing = 1;
		twop++;
	}
	CView::OnLButtonDown(nFlags, point);

}


void CMyCadView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针
	COLORREF color = pMainFrame->m_toolBoxView.m_toolDialog.currentColor;	//获取颜色
	
	endPoint = point;
	while (endPoint == beginPoint)	//起点终点想同，退出
	{
		return;
	}


	if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWLINE)	//判断操作是否是画线
	{
		
		this->SetLine(beginPoint, endPoint, color,currentStep);

		Invalidate(false);

		beginPoint = CPoint(0, 0);	//重置点
		endPoint = CPoint(0, 0);
		
		currentStep++;	//绘制步骤+1
		
		this->SetTreeDialog(currentStep,_T("绘制直线"));

	}
	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWRECT)	//判断操作是否是画矩形
	{
		

		this->SetRect(beginPoint, CPoint(endPoint.x, beginPoint.y), endPoint, CPoint(beginPoint.x, endPoint.y), color, currentStep);

		Invalidate(false);

		beginPoint = CPoint(0, 0);	//重置点
		endPoint = CPoint(0, 0);

		currentStep++;	//绘制步骤+1

		this->SetTreeDialog(currentStep, _T("绘制矩形"));

	}
	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWCIRCLE)
	{
		this->SetCircle(beginPoint, endPoint, color, currentStep);

		Invalidate(false);

		beginPoint = CPoint(0, 0);	//重置点
		endPoint = CPoint(0, 0);

		currentStep++;	//绘制步骤+1

		this->SetTreeDialog(currentStep, _T("绘制圆形"));
	}
	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::MOVEOBJECT)	//移动事件
	{
		beginTransform = false;
	}

	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWFILLRECT)	//绘制实心矩形
	{
		this->SetFillRect(beginPoint, endPoint, color, currentStep);

		Invalidate(false);

		beginPoint = CPoint(0, 0);	//重置点
		endPoint = CPoint(0, 0);

		currentStep++;	//绘制步骤+1

		this->SetTreeDialog(currentStep, _T("绘制实心矩形"));
	}
	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWFILLCIRCLE)	//绘制实心矩形
	{
		this->SetFillCircle(beginPoint, endPoint, color, currentStep);

		Invalidate(false);

		beginPoint = CPoint(0, 0);	//重置点
		endPoint = CPoint(0, 0);

		currentStep++;	//绘制步骤+1

		this->SetTreeDialog(currentStep, _T("绘制实心圆形"));
	}
	else if(pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWBEZIER)	//判断操作是否是画线
	{
		
		this->SetBezier(beginPoint, endPoint, color, currentStep);

		Invalidate(false);

		beginPoint = CPoint(0, 0);	//重置点
		endPoint = CPoint(0, 0);

		currentStep++;	//绘制步骤+1

		this->SetTreeDialog(currentStep, _T("绘制贝塞尔曲线"));

	}
	else if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel == ToolDialog::DRAWYUANHU)	//绘制圆弧
	{
		if (ing > 0)
		{
			ing = 0;
			twop = 0;
			this->SetRoundCircle(beginPoint, point, beginPoint2, beginPoint3, color, currentStep - 1);

			beginPoint = CPoint(0, 0);	//重置点
			beginPoint2 = CPoint(0, 0);
			endPoint = CPoint(0, 0);

			this->SetTreeDialog(currentStep, _T("绘制圆弧"));
			Invalidate();
		}
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
		currentEditStep = pMainFrame->m_treeBoxView.m_treeDialog.tree_currentStep;	//获取选中的图形
		if (currentEditStep < 0)	//没有选中图形，直接退出
		{

			
			return;
		}
					

		
		
		if (editSteps[currentEditStep].type == LINE)	//移动的对象是线条
		{
			COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色
			CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
			CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);


			//p1 += (point - editSteps[currentStep].centerPoint);//获取移动后的点
			//p2 += (point - editSteps[currentStep].centerPoint);

			int dx = point.x - editSteps[currentEditStep].centerPoint.x;	//获取位移量
			int dy = point.y - editSteps[currentEditStep].centerPoint.y;

			p1 = MyTransform::myglTranslatef(dx, dy, &p1);	//位移关键点
			p2 = MyTransform::myglTranslatef(dx, dy, &p2);
				
			this->SetLine(p1, p2, color, currentEditStep);	//重新绘制

		}

		else if (editSteps[currentEditStep].type == CIRCLE)	//移动的对象是线条
		{
			COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色
			CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
			CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

			int dx = point.x - editSteps[currentEditStep].centerPoint.x;	//获取位移量
			int dy = point.y - editSteps[currentEditStep].centerPoint.y;

			p1 = MyTransform::myglTranslatef(dx, dy, &p1);	//位移关键点
			p2 = MyTransform::myglTranslatef(dx, dy, &p2);

			this->SetCircle(p1, p2, color, currentEditStep);	//重新绘制

		}
		else if (editSteps[currentEditStep].type == RECT)	//移动的对象是线条
		{
			COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色
			CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
			CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);
			CPoint p3 = CPoint(editSteps[currentEditStep].point.next->next->x, editSteps[currentEditStep].point.next->next->y);
			CPoint p4 = CPoint(editSteps[currentEditStep].point.next->next->next->x, editSteps[currentEditStep].point.next->next->next->y);
		

			int dx = point.x - editSteps[currentEditStep].centerPoint.x;	//获取位移量
			int dy = point.y - editSteps[currentEditStep].centerPoint.y;

			p1 = MyTransform::myglTranslatef(dx, dy, &p1);	//位移关键点
			p2 = MyTransform::myglTranslatef(dx, dy, &p2);
			p3 = MyTransform::myglTranslatef(dx, dy, &p3);
			p4 = MyTransform::myglTranslatef(dx, dy, &p4);

			this->SetRect(p1, p2,p3,p4, color, currentEditStep);	//重新绘制

		}
		else if(editSteps[currentEditStep].type == FILLRECT)	//移动的对象是实心矩形
		{
			COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色
			CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
			CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

			int dx = point.x - editSteps[currentEditStep].centerPoint.x;	//获取位移量
			int dy = point.y - editSteps[currentEditStep].centerPoint.y;

			p1 = MyTransform::myglTranslatef(dx, dy, &p1);	//位移关键点
			p2 = MyTransform::myglTranslatef(dx, dy, &p2);

			this->SetFillRect(p1, p2, color, currentEditStep);	//重新绘制

		}
		else if (editSteps[currentEditStep].type == FILLCIRCLE)	//移动的对象是实心矩形
		{
			COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色
			CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
			CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

			int dx = point.x - editSteps[currentEditStep].centerPoint.x;	//获取位移量
			int dy = point.y - editSteps[currentEditStep].centerPoint.y;

			p1 = MyTransform::myglTranslatef(dx, dy, &p1);	//位移关键点
			p2 = MyTransform::myglTranslatef(dx, dy, &p2);

			this->SetFillCircle(p1, p2, color, currentEditStep);	//重新绘制

		}
		else if (editSteps[currentEditStep].type == BEZIER)	//移动的对象是线条
		{
			COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色
			CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
			CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

			int dx = point.x - editSteps[currentEditStep].centerPoint.x;	//获取位移量
			int dy = point.y - editSteps[currentEditStep].centerPoint.y;

			p1 = MyTransform::myglTranslatef(dx, dy, &p1);	//位移关键点
			p2 = MyTransform::myglTranslatef(dx, dy, &p2);

			this->SetBezier(p1, p2, color, currentEditStep);	//重新绘制

		}
		else if (editSteps[currentEditStep].type == ROUNDCIRCLE && !ing)	//移动的对象是圆弧
		{

			COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

			//点1为左点 点2为右点 点三为判定方向的点 点四为圆心点
			CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
			CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);
			CPoint p3 = CPoint(editSteps[currentEditStep].point.next->next->x, editSteps[currentEditStep].point.next->next->y);
			CPoint p4 = CPoint(editSteps[currentEditStep].point.next->next->next->x, editSteps[currentEditStep].point.next->next->next->y);

			int dx = point.x - editSteps[currentEditStep].centerPoint.x;	//获取位移量
			int dy = point.y - editSteps[currentEditStep].centerPoint.y;

			p1 = MyTransform::myglTranslatef(dx, dy, &p1);	//位移关键点
			p2 = MyTransform::myglTranslatef(dx, dy, &p2);
			p3 = MyTransform::myglTranslatef(dx, dy, &p3);
			p4 = MyTransform::myglTranslatef(dx, dy, &p4);



			this->SetRoundCircle(p1, p4, p2, p3, color, currentEditStep);//重新绘制

		}
		

		Invalidate();


	}
	if (pMainFrame->m_toolBoxView.m_toolDialog.currentModel==ToolDialog::DRAWYUANHU && ing)	//画圆弧事件
	{
		CClientDC pDC(this);
		if (ing == 1)//正在选择
		{
			CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针
			COLORREF color = pMainFrame->m_toolBoxView.m_toolDialog.currentColor;	//获取颜色

			endPoint = point;

			if (beginPoint.x != endPoint.x && beginPoint != endPoint)
			{
				pDC.MoveTo(beginPoint);
				pDC.LineTo(beginPoint2);
				this->SetRoundCircle(beginPoint, point, beginPoint2, beginPoint3, color, currentStep - 1);
				Invalidate();
			}
		}
	

	}
	CView::OnMouseMove(nFlags, point);
}


//设置线条
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
//设置矩形
void CMyCadView::SetRect(CPoint p1, CPoint p2, CPoint p3,CPoint p4, COLORREF color, int s)
{
	DrawRect MyDrawRect;
	MyDrawRect.drawRect(p1, p2, p3, p4, color);
	DrawRect::pStepPoint p = MyDrawRect.stepPoint;	//获取MyDrawLine的像素点
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

	editSteps[s].type = RECT; //绘制的是线条
	editSteps[s].centerPoint = CPoint((p1.x + p3.x) / 2, (p1.y + p3.y) / 2);//中心点
	editSteps[s].point.x = p1.x;	//写入关键点数据
	editSteps[s].point.y = p1.y;
	editSteps[s].point.color = color;
	Points* newPoint = new Points;
	editSteps[s].point.next = newPoint;
	newPoint->x = p2.x;	//写入关键点数据
	newPoint->y = p2.y;
	newPoint->color = color;
	newPoint->next = NULL;
	Points* newPoint2 = new Points;
	editSteps[s].point.next->next = newPoint2;
	newPoint2->x = p3.x;	//写入关键点数据
	newPoint2->y = p3.y;
	newPoint2->color = color;
	newPoint2->next = NULL;
	Points* newPoint3 = new Points;
	editSteps[s].point.next->next->next = newPoint3;
	newPoint3->x = p4.x;	//写入关键点数据
	newPoint3->y = p4.y;
	newPoint3->color = color;
	newPoint3->next = NULL;
}

//设置圆
void CMyCadView::SetCircle(CPoint p1, CPoint p2, COLORREF color, int s)
{
	DrawCircle MyDrawCircle;
	MyDrawCircle.MidPntCircle(p1.x, p1.y, p2.x, p2.y, color);
	DrawLine::pStepPoint p = MyDrawCircle.stepPoint;	//获取MyDrawLine的像素点
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
	editSteps[s].type = CIRCLE; //绘制的是线条
	editSteps[s].centerPoint = CPoint(p1.x, p1.y);//中心点
	editSteps[s].point.x = p1.x;	//写入关键点数据
	editSteps[s].point.y = p1.y;
	editSteps[s].point.color = color;
	Points* newPoint = new Points;
	editSteps[s].point.next = newPoint;
	newPoint->x = p2.x;	//写入关键点数据
	newPoint->y = p2.y;
	newPoint->color = color;
	newPoint->next = NULL;
}


//设置实心矩形
void CMyCadView::SetFillRect(CPoint p1, CPoint p2, COLORREF color, int s)
{
	DrawFillRect MyDrawFillRect;
	MyDrawFillRect.DrawRectFunc(p1.x, p1.y, p2.x, p2.y, color);	//获取实心矩形的所有点，存储到MyDrawFillRect对象的stepPoint链表里面

	DrawFillRect::pStepPoint p = MyDrawFillRect.stepPoint;	//获取DrawFillRect的像素点的头结点

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
	editSteps[s].type = FILLRECT; //绘制的是实心矩形
	editSteps[s].centerPoint = CPoint((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);//中心点
	editSteps[s].point.x = p1.x;	//写入关键点数据
	editSteps[s].point.y = p1.y;
	editSteps[s].point.color = color;
	Points* newPoint = new Points;
	editSteps[s].point.next = newPoint;
	newPoint->x = p2.x;	//写入关键点数据
	newPoint->y = p2.y;
	newPoint->color = color;
	newPoint->next = NULL;


}

//绘制实心圆
void CMyCadView::SetFillCircle(CPoint p1, CPoint p2, COLORREF color, int s)
{
	DrawFillCircle MyDrawFillCircle;
	MyDrawFillCircle.drawFillCircle(p1.x, p1.y, p2.x, p2.y, color);	//获取实心矩形的所有点，存储到MyDrawFillRect对象的stepPoint链表里面

	DrawFillCircle::pStepPoint p = MyDrawFillCircle.stepPoint;	//获取DrawFillRect的像素点的头结点

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
	editSteps[s].type = FILLCIRCLE; //绘制的是实心矩形
	editSteps[s].centerPoint = p1;//中心点
	editSteps[s].point.x = p1.x;	//写入关键点数据
	editSteps[s].point.y = p1.y;
	editSteps[s].point.color = color;
	Points* newPoint = new Points;
	editSteps[s].point.next = newPoint;
	newPoint->x = p2.x;	//写入关键点数据
	newPoint->y = p2.y;
	newPoint->color = color;
	newPoint->next = NULL;
}

//设置贝塞尔
void CMyCadView::SetBezier(CPoint p1, CPoint p2, COLORREF color, int s)
{
	DrawBezier MyDrawBezier;
	MyDrawBezier.drawBezier(p1, p2, color);	//获取实心矩形的所有点，存储到MyDrawFillRect对象的stepPoint链表里面

	DrawBezier::pStepPoint p = MyDrawBezier.stepPoint;	//获取DrawFillRect的像素点的头结点

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
	editSteps[s].type = BEZIER; //绘制的是实心矩形
	editSteps[s].centerPoint = CPoint((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);//中心点
	editSteps[s].point.x = p1.x;	//写入关键点数据
	editSteps[s].point.y = p1.y;
	editSteps[s].point.color = color;
	Points* newPoint = new Points;
	editSteps[s].point.next = newPoint;
	newPoint->x = p2.x;	//写入关键点数据
	newPoint->y = p2.y;
	newPoint->color = color;
	newPoint->next = NULL;
}


//设置圆弧(x1为第一个点 p1只取圆弧圆心的x坐标 p2为另一个点)
void CMyCadView::SetRoundCircle(CPoint x1, CPoint p1, CPoint p2, CPoint p3, COLORREF color, int s)
{
	//p1只用到y
	double midx, midy, k, k2, b, b2, p1x;
	//用来判断的
	int fuhao;
	midx = (x1.x + p2.x) / 2;
	midy = (x1.y + p2.y) / 2;
	k = (double)(p2.y - x1.y) / (double)(p2.x - x1.x);
	b = p2.y - k * p2.x;
	k2 = -(1 / k);
	b2 = midy - k2 * midx;
	if (k * p3.x + b - p3.y < 0)
		fuhao = -1;
	else fuhao = 1;

	CPoint yuanxin;
	yuanxin.x = p1.x;
	yuanxin.y = k2 * p1.x + b2;

	DrawCircle MyDrawCircle;
	MyDrawCircle.MidPntCircle(yuanxin.x, yuanxin.y, p2.x, p2.y, color);
	DrawLine::pStepPoint p = MyDrawCircle.stepPoint;	//获取MyDrawLine的像素点
	stepPoints[s].step = s;	//写入操作步骤
	Points* q = &(stepPoints[s].point);	//获取表头结点
	while (p)	//写入像素点数据
	{
		q->x = p->x;
		q->y = p->y;
		q->color = p->color;
		if (fuhao * (k * p->x + b - p->y) > 0)
			//if (k * p1.x + b - p1.y < 0 && k * p->x + b - p->y < 0 || k * p1.x + b - p1.y > 0 && k * p->x + b - p->y > 0)
		{
			Points* nq = new Points;
			nq->next = NULL;
			q->next = nq;
			q = q->next;
		}
		p = p->next;

	}

	//保存操作记录
	if (ing == 0)
	{
		//点1为左点 点2为右点 点三为判定方向的点 点四为圆心点
		editSteps[s].type = ROUNDCIRCLE; //绘制的是线条
		editSteps[s].centerPoint = CPoint(midx, midy);//中心点
		editSteps[s].point.x = x1.x;	//写入关键点1数据
		editSteps[s].point.y = x1.y;
		editSteps[s].point.color = color;
		Points* newPoint = new Points;
		editSteps[s].point.next = newPoint;
		newPoint->x = p2.x;	//写入关键点2数据
		newPoint->y = p2.y;
		newPoint->color = color;
		newPoint->next = NULL;
		editSteps[s].point.next = newPoint;
		newPoint = new Points;
		newPoint->x = p3.x;	//写入关键点3数据
		newPoint->y = p3.y;
		newPoint->color = color;
		newPoint->next = NULL;
		editSteps[s].point.next->next = newPoint;
		newPoint = new Points;
		newPoint->x = p1.x;	//写入关键点4数据
		newPoint->y = p1.y;
		newPoint->color = color;
		newPoint->next = NULL;
		editSteps[s].point.next->next->next = newPoint;
	}
}


// 导出图片
void CMyCadView::OnExportImage()
{
	// TODO: 在此添加命令处理程序代码

	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);                  //获取画布大小
	HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);	//创建兼容位图
	HDC hdc = CreateCompatibleDC(dc);      //创建兼容DC，以便将图像保存为不同的格式
	HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);	//将位图选入DC，并保存返回值 
	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);	//将屏幕DC的图像复制到内存DC中


	CImage image;
	image.Attach(hbitmap);                //将位图转化为一般图像

	CString  strFilter = _T("图片文件(*.jpg)|*.jpg||");
	CFileDialog dlg(FALSE, _T("jpg"), _T("MyCadImage"), NULL, strFilter);

	if (dlg.DoModal() != IDOK)	//模态窗口显示
		return;

	CString strFileName;          //文件路径


	strFileName = dlg.m_ofn.lpstrFile;


	HRESULT hResult = image.Save(strFileName);     //保存图像

	if (FAILED(hResult))
		MessageBox(_T("保存图像文件失败！"));
	else
		MessageBox(_T("图像保存成功！"));

	image.Detach();
	SelectObject(hdc, hOldMap);

	
}


//捕捉快捷键
BOOL CMyCadView::PreTranslateMessage(MSG* pMsg)
{
	
	static bool m_ctrl_down = false;//此函数第一次调用的时候初始化

	if (pMsg->message == WM_KEYDOWN)
	{

		switch (pMsg->wParam)
		{
		case 'Z'://Ctrl + Z
			if (m_ctrl_down)	//Ctrl+Z按下
			{
				//AfxMessageBox(_T("Ctrl + Z key down")); 
				if (currentStep > 0)
				{
					currentStep--;
					CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针
					pMainFrame->m_treeBoxView.m_treeDialog.DelTreeItem();
					
					Invalidate();
				}

				return TRUE;
			}
			break;
		case 'N'://Ctrl + N
			if (m_ctrl_down)	//Ctrl+N按下
			{
				
				OnFileNew();
				return TRUE;
			}
			break;
		case 'S'://Ctrl + S
			if (m_ctrl_down)	//Ctrl+S按下
			{
				OnFileSave();
				return TRUE;
			}
			break;
		case 'O'://Ctrl + O
			if (m_ctrl_down)	//Ctrl+O按下
			{

				OnFileOpen();
				return TRUE;
			}
			break;

		case VK_CONTROL:
			m_ctrl_down = true; return TRUE;
		default:
			return TRUE;
		}
	}
	if (pMsg->message == WM_KEYUP)
	{
		switch (pMsg->wParam)
		{
		case VK_CONTROL:
			m_ctrl_down = false; return TRUE;
		}
	}

	return CView::PreTranslateMessage(pMsg);
}






//新建场景
void CMyCadView::OnFileNew()	
{
	// TODO: 在此添加命令处理程序代码
	currentStep = 0;
	currentEditStep = -1;
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针
	pMainFrame->m_treeBoxView.m_treeDialog.DelAllTreeItem(); //删除树状图
	
	

	Invalidate();
}



//保存文件
void CMyCadView::OnFileSave() 
{
	// TODO: 在此添加命令处理程序代码
	TCHAR szFilter[] = _T("json文件(*.json)|*.json||");
	//构造保存文件对话框   
	CFileDialog fileDlg(FALSE, _T("json"), _T("MyCad"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString FileName;

	// 显示保存文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
		FileName = fileDlg.GetPathName();
		
		JsonClass MyJson;
		int i = 0;
		while (i < currentStep)	//写入每一步的操作步骤到json中
		{
			pEditStep  p = editSteps[i];

			if (p.type == LINE)
				MyJson.SetJsonLineStep(p.centerPoint.x, p.centerPoint.y, p.point.x, p.point.y, GetRValue(p.point.color), GetGValue(p.point.color), GetBValue(p.point.color), p.point.next->x, p.point.next->y, GetRValue(p.point.next->color), GetGValue(p.point.next->color), GetBValue(p.point.next->color));
			else if (p.type == CIRCLE)
				MyJson.SetJsonCircleStep(p.centerPoint.x, p.centerPoint.y, p.point.x, p.point.y, GetRValue(p.point.color), GetGValue(p.point.color), GetBValue(p.point.color), p.point.next->x, p.point.next->y, GetRValue(p.point.next->color), GetGValue(p.point.next->color), GetBValue(p.point.next->color));
			else if (p.type == RECT)
			{
				CPoint pc = p.centerPoint;
				Points p1 = p.point;
				Points* p2 = p.point.next;
				Points* p3 = p.point.next->next;
				Points* p4 = p.point.next->next->next;

				MyJson.SetJsonRectStep(pc.x, pc.y, GetRValue(p1.color), GetGValue(p1.color), GetBValue(p1.color), p1.x, p1.y, p2->x, p2->y, p3->x, p3->y, p4->x, p4->y);
			}
				
			else if (p.type == FILLRECT)
				MyJson.SetJsonFillRectStep(p.centerPoint.x, p.centerPoint.y, p.point.x, p.point.y, GetRValue(p.point.color), GetGValue(p.point.color), GetBValue(p.point.color), p.point.next->x, p.point.next->y, GetRValue(p.point.next->color), GetGValue(p.point.next->color), GetBValue(p.point.next->color));
			else if (p.type == FILLCIRCLE)
				MyJson.SetJsonFillCircleStep(p.centerPoint.x, p.centerPoint.y, p.point.x, p.point.y, GetRValue(p.point.color), GetGValue(p.point.color), GetBValue(p.point.color), p.point.next->x, p.point.next->y, GetRValue(p.point.next->color), GetGValue(p.point.next->color), GetBValue(p.point.next->color));
			else if (p.type == BEZIER)
				MyJson.SetJsonBezierStep(p.centerPoint.x, p.centerPoint.y, p.point.x, p.point.y, GetRValue(p.point.color), GetGValue(p.point.color), GetBValue(p.point.color), p.point.next->x, p.point.next->y, GetRValue(p.point.next->color), GetGValue(p.point.next->color), GetBValue(p.point.next->color));
			else if (p.type == ROUNDCIRCLE)
			{
				CPoint pc = p.centerPoint;
				Points p1 = p.point;
				Points *p2 = p.point.next;
				Points *p3 = p.point.next->next;
				Points *p4 = p.point.next->next->next;

				MyJson.SetJsonRoundCircleStep(pc.x, pc.y, GetRValue(p1.color), GetGValue(p1.color), GetBValue(p1.color), p1.x, p1.y, p2->x, p2->y, p3->x, p3->y, p4->x, p4->y);
			}
				
			i++;
		}

		MyJson.ExportJsonFile(FileName);	//导出json文件
		MessageBox(_T("导出文件成功"));
	}
	else
		return;



}


//打开文件
void CMyCadView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	OnFileNew();	//新建场景
	JsonClass MyJson;
	
	MyJson.OpenJsonFile();	//打开json文件，将数据加载到MyJson变量中
	
	for (int i = 0; i < MyJson.GetJsonCount(); i++)	//写入数据到存储数组里
	{
		CString type = MyJson.GetJsonStepType(i + 1).c_str();
		if (type==_T("LINE"))
		{
		
			CPoint p1 = MyJson.GetPoint(i + 1, 1);
			CPoint p2 = MyJson.GetPoint(i + 1, 2);
			COLORREF color = MyJson.GetColor(i + 1, 1);
			this->SetLine(p1,p2,color,i);
			currentStep++;	//绘制步骤+1
			this->SetTreeDialog(currentStep, _T("绘制直线"));
			
		}
			
		else if (type == _T("CIRCLE"))
		{
			CPoint p1 = MyJson.GetPoint(i + 1, 1);
			CPoint p2 = MyJson.GetPoint(i + 1, 2);
			COLORREF color = MyJson.GetColor(i + 1, 1);
			this->SetCircle(p1, p2, color, i);
			currentStep++;	//绘制步骤+1
			this->SetTreeDialog(currentStep, _T("绘制圆形"));
		}
		else if (type == _T("RECT"))
		{
			CPoint p1 = MyJson.GetPoint(i + 1, 1);
			CPoint p2 = MyJson.GetPoint(i + 1, 2);
			CPoint p3 = MyJson.GetPoint(i + 1, 3);
			CPoint p4 = MyJson.GetPoint(i + 1, 4);
			COLORREF color = MyJson.GetColor(i + 1, 1);
			this->SetRect(p1, p2, p3,p4,color, i);
			currentStep++;	//绘制步骤+1
			this->SetTreeDialog(currentStep, _T("绘制矩形"));
		}
		else if (type == _T("FILLRECT"))
		{
			CPoint p1 = MyJson.GetPoint(i + 1, 1);
			CPoint p2 = MyJson.GetPoint(i + 1, 2);
			COLORREF color = MyJson.GetColor(i + 1, 1);
			this->SetFillRect(p1, p2, color, i);
			currentStep++;	//绘制步骤+1
			this->SetTreeDialog(currentStep, _T("绘制实心矩形"));
		}
		else if (type == _T("FILLCIRCLE"))
		{
			CPoint p1 = MyJson.GetPoint(i + 1, 1);
			CPoint p2 = MyJson.GetPoint(i + 1, 2);
			COLORREF color = MyJson.GetColor(i + 1, 1);
			this->SetFillCircle(p1, p2, color, i);
			currentStep++;	//绘制步骤+1
			this->SetTreeDialog(currentStep, _T("绘制实心圆形"));
		}
		else if (type == _T("BEZIER"))
		{
			CPoint p1 = MyJson.GetPoint(i + 1, 1);
			CPoint p2 = MyJson.GetPoint(i + 1, 2);
			COLORREF color = MyJson.GetColor(i + 1, 1);
			this->SetBezier(p1, p2, color, i);
			currentStep++;	//绘制步骤+1
			this->SetTreeDialog(currentStep, _T("绘制贝塞尔曲线"));
		}
		else if (type == _T("ROUNDCIRCLE"))
		{
			CPoint p1 = MyJson.GetPoint(i + 1, 1);
			CPoint p2 = MyJson.GetPoint(i + 1, 2);
			CPoint p3 = MyJson.GetPoint(i + 1, 3);
			CPoint p4 = MyJson.GetPoint(i + 1, 4);

			COLORREF color = MyJson.GetColor(i + 1, 1);
			this->SetRoundCircle(p1, p2, p3, p4, color, i);
			currentStep++;	//绘制步骤+1
			this->SetTreeDialog(currentStep, _T("绘制圆弧"));
		}
	}
	Invalidate();
	MessageBox(_T("打开文件成功"));
	
}



//导出视频
void CMyCadView::OnExportVideo()
{
	
	// TODO: 在此添加命令处理程序代码
	TCHAR szFilter[] = _T("视频文件(*.avi)|*.avi||");
	//构造保存文件对话框   
	CFileDialog fileDlg(FALSE, _T("avi"), _T("MyCad"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	
	// 显示保存文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
		video_path = fileDlg.GetPathName();
	}
	else
		return;
	//清空屏幕
	is_create_video = true;
	Invalidate();
	
	//逐步绘制图形
	SetTimer(1, 500, NULL); //创建定时器，每隔0.5s执行一次


	
}

//计时器
void CMyCadView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)

	{

	case 1:
		if (video_step == currentStep)
		{
			KillTimer(1);	//关闭定时器
			video_step = 0; //重置
			is_create_video = false;
			system(_T("..\\..\\ffmpeg\\bin\\ffmpeg.exe -r 1 -i .\\temp\\%03d.jpg ")+video_path+_T(" -y"));
			DeleteDirectory(_T(".\\temp"));
			MessageBox(_T("导出视频成功"));
			return;
		}


		CDC * pDC = GetDC();//初始化指针pDC

		this->DrawStepPoints(pDC,video_step); //绘制第video_step图形

		ReleaseDC(pDC);//释放指针
		video_step++;
		break;
	
	}

	CView::OnTimer(nIDEvent);
}

// 绘制单步骤的点，并把该步骤图形保存成图片
void CMyCadView::DrawStepPoints(CDC* pDC, int step)
{

	Points* p = &(stepPoints[step].point);	
	while (p)
	{
		pDC->SetPixel(p->x, p->y, p->color);
		p = p->next;
	}
	
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);                  //获取画布大小
	HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);	//创建兼容位图
	HDC hdc = CreateCompatibleDC(dc);      //创建兼容DC，以便将图像保存为不同的格式
	HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);	//将位图选入DC，并保存返回值 
	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);	//将屏幕DC的图像复制到内存DC中

	CImage image;
	image.Attach(hbitmap);                //将位图转化为一般图像

	/*CString path = _T("‪C:/Users/huangPeiXin/Desktop/temp/00.jpg");
	CString strFileName = path;*/
	CString tempPath;
	tempPath.Format(".\\temp\\%03d.jpg", step);

	HRESULT hResult = image.Save(tempPath);     //保存图像

	
	image.Detach();
	SelectObject(hdc, hOldMap);
}

//删除文件夹下所有文件
bool CMyCadView::DeleteDirectory(CString  strDir)
{
	if (strDir.IsEmpty())
		return false;

	//   首先删除文件及子文件夹     
	CFileFind   ff;
	BOOL   bFound = ff.FindFile(strDir + L"\\*", 0);
	while (bFound)
	{
		bFound = ff.FindNextFile();
		if (ff.GetFileName() == "." || ff.GetFileName() == "..")
			continue;
		//   去掉文件(夹)只读等属性     
		SetFileAttributes(ff.GetFilePath(), FILE_ATTRIBUTE_NORMAL);
		if (ff.IsDirectory())
		{
			//   递归删除子文件夹     
			DeleteDirectory(ff.GetFilePath());
			RemoveDirectory(ff.GetFilePath());
		}
		else
		{
			//   删除文件     
			DeleteFile(ff.GetFilePath());
		}
	}
	ff.Close();

	//   然后删除该文件夹     
	//RemoveDirectory(strDir);  
	return true;
}



//创建gl窗口
void CMyCadView::OnShowGLDialog()
{
	// TODO: 在此添加命令处理程序代码
	CreateGLDialog glDialog;
	glDialog.DoModal();
}


//旋转
void CMyCadView::RotateObject()
{
	float angle, x, y;
	bool isCenter;
	RotateDialog dlg = new RotateDialog;
	dlg.DoModal();

	if (!dlg.isRotate)
		return;

	angle = dlg.angle * PI / 180;//旋转角度
	x = dlg.RotateX;//关于旋转x坐标
	y = dlg.RotateY;//关于旋转y坐标
	isCenter = dlg.isCenter;

	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针
	//当前只修改这一步骤下的图形
	currentEditStep = pMainFrame->m_treeBoxView.m_treeDialog.tree_currentStep;	//获取选中的图形
	if (currentEditStep < 0)	//没有选中图形，直接退出
		return;


	if (editSteps[currentEditStep].type == LINE)	//移动的对象是线条
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

		CPoint pc = editSteps[currentEditStep].centerPoint;

		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);
		

		if (isCenter)
		{
			p1 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p1);//位移关键点
			p2 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p2);//位移关键点
			
		}
		else
		{
			p1 = MyTransform::myglRotatef(angle, x, y, &p1);//位移关键点
			p2 = MyTransform::myglRotatef(angle, x, y, &p2);//位移关键点
		
		
		}


		this->SetLine(p1, p2, color, currentEditStep);	//重新绘制
	}
	else if (editSteps[currentEditStep].type == RECT)	//移动的对象是线条
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

		CPoint pc = editSteps[currentEditStep].centerPoint;

		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);
		CPoint p3 = CPoint(editSteps[currentEditStep].point.next->next->x, editSteps[currentEditStep].point.next->next->y);
		CPoint p4 = CPoint(editSteps[currentEditStep].point.next->next->next->x, editSteps[currentEditStep].point.next->next->next->y);
		if (isCenter)
		{
			p1 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p1);//位移关键点
			p2 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p2);//位移关键点
			p3 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p3);//位移关键点
			p4 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p4);//位移关键点
		}
		else
		{
			p1 = MyTransform::myglRotatef(angle, x, y, &p1);//位移关键点
			p2 = MyTransform::myglRotatef(angle, x, y, &p2);//位移关键点
			p3 = MyTransform::myglRotatef(angle, x, y, &p3);//位移关键点
			p4 = MyTransform::myglRotatef(angle, x, y, &p4);//位移关键点
		}
		this->SetRect(p1, p2, p3,p4,color, currentEditStep);	//重新绘制
	}
	else if (editSteps[currentEditStep].type == CIRCLE)	//移动的对象是线条
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

		CPoint pc = editSteps[currentEditStep].centerPoint;

		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

		if (isCenter)
		{
			p1 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p1);//位移关键点
			p2 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p2);//位移关键点
		}
		else
		{
			p1 = MyTransform::myglRotatef(angle, x, y, &p1);//位移关键点
			p2 = MyTransform::myglRotatef(angle, x, y, &p2);//位移关键点

		}

		this->SetCircle(p1, p2, color, currentEditStep);	//重新绘制
	}
	else if (editSteps[currentEditStep].type == BEZIER)	//移动的对象是线条
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

		CPoint pc = editSteps[currentEditStep].centerPoint;

		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

		if (isCenter)
		{
			p1 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p1);//位移关键点
			p2 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p2);//位移关键点
		}
		else
		{
			p1 = MyTransform::myglRotatef(angle, x, y, &p1);//位移关键点
			p2 = MyTransform::myglRotatef(angle, x, y, &p2);//位移关键点

		}

		this->SetBezier(p1, p2, color, currentEditStep);	//重新绘制
	}
	else if (editSteps[currentEditStep].type == FILLRECT)	//移动的对象是线条
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

		CPoint pc = editSteps[currentEditStep].centerPoint;

		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

		if (isCenter)
		{
			p1 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p1);//位移关键点
			p2 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p2);//位移关键点
		}
		else
		{
			p1 = MyTransform::myglRotatef(angle, x, y, &p1);//位移关键点
			p2 = MyTransform::myglRotatef(angle, x, y, &p2);//位移关键点

		}

		this->SetFillRect(p1, p2, color, currentEditStep);	//重新绘制
	}
	else if (editSteps[currentEditStep].type == FILLCIRCLE)	//移动的对象是线条
	{
	COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

	CPoint pc = editSteps[currentEditStep].centerPoint;

	CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
	CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

	if (isCenter)
	{
		p1 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p1);//位移关键点
		p2 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p2);//位移关键点
	}
	else
	{
		p1 = MyTransform::myglRotatef(angle, x, y, &p1);//位移关键点
		p2 = MyTransform::myglRotatef(angle, x, y, &p2);//位移关键点

	}

	this->SetFillCircle(p1, p2, color, currentEditStep);	//重新绘制
	}
	else if (editSteps[currentEditStep].type == ROUNDCIRCLE)	//移动的对象是线条
	{
	COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

	CPoint pc = editSteps[currentEditStep].centerPoint;

	CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
	CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);
	CPoint p3 = CPoint(editSteps[currentEditStep].point.next->next->x, editSteps[currentEditStep].point.next->next->y);
	CPoint p4 = CPoint(editSteps[currentEditStep].point.next->next->next->x, editSteps[currentEditStep].point.next->next->next->y);


	if (isCenter)
	{
		p1 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p1);//位移关键点
		p2 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p2);//位移关键点
		p3 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p3);//位移关键点
		p4 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p4);//位移关键点
	}
	else
	{
		p1 = MyTransform::myglRotatef(angle, x, y, &p1);//位移关键点
		p2 = MyTransform::myglRotatef(angle, x, y, &p2);//位移关键点
		p3 = MyTransform::myglRotatef(angle, x, y, &p3);//位移关键点
		p4 = MyTransform::myglRotatef(angle, x, y, &p4);//位移关键点

	}

	this->SetRoundCircle(p1, p2,p3,p4, color, currentEditStep);	//重新绘制
	}
	Invalidate();


}

//缩放
void CMyCadView::ScaleObject()
{
	float x, y;
	ScaleDialog dlg = new ScaleDialog;
	dlg.DoModal();
	if (!dlg.IsScale)
		return;
	x = dlg.ScaleX;//关于旋转x坐标
	y = dlg.ScaleY;//关于旋转y坐标

	if (x == 0)
		x = 1;
	if (y== 0)
		y = 1;
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针
//当前只修改这一步骤下的图形
	currentEditStep = pMainFrame->m_treeBoxView.m_treeDialog.tree_currentStep;	//获取选中的图形
	if (currentEditStep < 0)	//没有选中图形，直接退出
		return;

	if (editSteps[currentEditStep].type == LINE)	//移动的对象是线条
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

		CPoint pc = editSteps[currentEditStep].centerPoint;
		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

		p1 = MyTransform::myglScalef(3, 3, pc, &p1);
		p2 = MyTransform::myglScalef(3, 3, pc, &p2);

		this->SetLine(p1, p2, color, currentEditStep);	//重新绘制
	}
	else if (editSteps[currentEditStep].type == RECT)	//移动的对象是填充矩形
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

		CPoint pc = editSteps[currentEditStep].centerPoint;

		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);
		CPoint p3 = CPoint(editSteps[currentEditStep].point.next->next->x, editSteps[currentEditStep].point.next->next->y);
		CPoint p4 = CPoint(editSteps[currentEditStep].point.next->next->next->x, editSteps[currentEditStep].point.next->next->next->y);

		p1 = MyTransform::myglScalef(x, y,pc, &p1);//缩放关键点
		p2 = MyTransform::myglScalef(x, y,pc, &p2);
		p3 = MyTransform::myglScalef(x, y,pc, &p3);
		p4 = MyTransform::myglScalef(x, y,pc, &p4);

		this->SetRect(p1, p2,p3,p4, color, currentEditStep);	//重新绘制
	}
	else if (editSteps[currentEditStep].type == FILLRECT)	//移动的对象是矩形
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

		CPoint pc = editSteps[currentEditStep].centerPoint;

		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

		p1 = MyTransform::myglScalef(x, y,pc, &p1);//缩放关键点
		p2 = MyTransform::myglScalef(x, y,pc, &p2);

		this->SetFillRect(p1, p2, color, currentEditStep);	//重新绘制
	}
	else if (editSteps[currentEditStep].type == CIRCLE)	//移动的对象是圆形
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

		CPoint pc = editSteps[currentEditStep].centerPoint;

		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

		p1 = MyTransform::myglScalef(x, y,pc, &p1);//缩放关键点
		p2 = MyTransform::myglScalef(x, y,pc, &p2);

		this->SetCircle(p1, p2, color, currentEditStep);	//重新绘制
	}
	else if (editSteps[currentEditStep].type == BEZIER)	//移动的对象是圆形
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

		CPoint pc = editSteps[currentEditStep].centerPoint;

		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

		p1 = MyTransform::myglScalef(x, y, pc, &p1);//缩放关键点
		p2 = MyTransform::myglScalef(x, y, pc, &p2);

		this->SetBezier(p1, p2, color, currentEditStep);	//重新绘制
	}
	else if (editSteps[currentEditStep].type == FILLCIRCLE)	//移动的对象是圆形
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

		CPoint pc = editSteps[currentEditStep].centerPoint;

		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

		p1 = MyTransform::myglScalef(x, y, pc, &p1);//缩放关键点
		p2 = MyTransform::myglScalef(x, y, pc, &p2);

		this->SetFillCircle(p1, p2, color, currentEditStep);	//重新绘制
	}
	else if (editSteps[currentEditStep].type == ROUNDCIRCLE)	//移动的对象是圆形
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色

		CPoint pc = editSteps[currentEditStep].centerPoint;


		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);
		CPoint p3 = CPoint(editSteps[currentEditStep].point.next->next->x, editSteps[currentEditStep].point.next->next->y);
		CPoint p4 = CPoint(editSteps[currentEditStep].point.next->next->next->x, editSteps[currentEditStep].point.next->next->next->y);


		
		p1 = MyTransform::myglScalef(x,y,pc, &p1);//位移关键点
		p2 = MyTransform::myglScalef(x,y,pc, &p2);//位移关键点
		p3 = MyTransform::myglScalef(x,y,pc, &p3);//位移关键点
		p4 = MyTransform::myglScalef(x,y,pc, &p4);//位移关键点
		
		this->SetRoundCircle(p1, p2, p3, p4, color, currentEditStep);	//重新绘制
	}
	Invalidate();
}