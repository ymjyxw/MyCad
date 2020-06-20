
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
#include "MainFrm.h"
#include "ToolDialog.h"
#include "MyTransform.h"
#include "JsonClass.h"
#include "CreateGLDialog.h"

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

	DrawPoints(pDC); //绘制所有图形
	
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
	
	CDC * pDC = GetDC();//初始化指针pDC
	
	CPoint cp = editSteps[step].centerPoint;
	CPoint ld = cp - CPoint(10, 10);
	CPoint rt = cp + CPoint(10, 10);

	CBrush NewBrush, *pOldBrush;
	NewBrush.CreateSolidBrush(RGB(255, 0, 0));
	pOldBrush = pDC->SelectObject(&NewBrush);
	pDC->Ellipse(CRect(ld, rt));
	pDC->SelectObject(pOldBrush);
	NewBrush.DeleteObject();
	ReleaseDC(pDC);//释放指针
	
}



void CMyCadView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	

	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针
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
		

		this->SetRect(beginPoint, endPoint, color, currentStep);

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

			int dx = point.x - editSteps[currentEditStep].centerPoint.x;	//获取位移量
			int dy = point.y - editSteps[currentEditStep].centerPoint.y;

			p1 = MyTransform::myglTranslatef(dx, dy, &p1);	//位移关键点
			p2 = MyTransform::myglTranslatef(dx, dy, &p2);

			this->SetRect(p1, p2, color, currentEditStep);	//重新绘制

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


		Invalidate();
		

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
void CMyCadView::SetRect(CPoint p1, CPoint p2, COLORREF color, int s)
{
	DrawRect MyDrawRect;
	MyDrawRect.drawRect(p1.x, p1.y, p2.x, p2.y, color);
	DrawRect::pStepPoint p = MyDrawRect.stepPoint;	//获取MyDrawLine的像素点
	stepPoints[s].step = s;	//写入操作步骤
	stepPoints[s].xl = p1.x;
	stepPoints[s].xr = p1.x;
	stepPoints[s].yt = p1.y;
	stepPoints[s].yb = p1.y;

	Points* q = &(stepPoints[s].point);	//获取表头结点

	while (p)	//写入像素点数据
	{
		//比较并更新边缘值
		if (p->x >= stepPoints[s].xl && p->x <= stepPoints[s].xr && p->y <= stepPoints[s].yt && p->y >= stepPoints[s].yb) {

		}
		else {//当需要更新图形的边值时
			if (p->x < stepPoints[s].xl) stepPoints[s].xl = p->x;
			if (p->x > stepPoints[s].xr) stepPoints[s].xr = p->x;
			if (p->y < stepPoints[s].yb) stepPoints[s].yb = p->y;
			if (p->y > stepPoints[s].yt) stepPoints[s].yt = p->y;
		}

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
				MyJson.SetJsonRectStep(p.centerPoint.x, p.centerPoint.y, p.point.x, p.point.y, GetRValue(p.point.color), GetGValue(p.point.color), GetBValue(p.point.color), p.point.next->x, p.point.next->y, GetRValue(p.point.next->color), GetGValue(p.point.next->color), GetBValue(p.point.next->color));
			else if (p.type == FILLRECT)
				MyJson.SetJsonFillRectStep(p.centerPoint.x, p.centerPoint.y, p.point.x, p.point.y, GetRValue(p.point.color), GetGValue(p.point.color), GetBValue(p.point.color), p.point.next->x, p.point.next->y, GetRValue(p.point.next->color), GetGValue(p.point.next->color), GetBValue(p.point.next->color));
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
			COLORREF color = MyJson.GetColor(i + 1, 1);
			this->SetRect(p1, p2, color, i);
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


//显示旋转对话框
void CMyCadView::RotateObject()
{
	//MessageBox(_T("显示旋转对话框"));

	float angle;
	//Todo:弹出对话框，输入旋转数据，然后获取

	//CtrPsDialog dlg = new CtrPsDialog;
	//dlg.DoModal();
	//angle = dlg.num1;
	angle = 45.0f;

	//Todo:获取当前修改的图形
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);//获取框架类指针

	//当前只修改这一步骤下的图形
	currentEditStep = pMainFrame->m_treeBoxView.m_treeDialog.tree_currentStep;	//获取选中的图形
	if (currentEditStep < 0)	//没有选中图形，直接退出
		return;

	//editSteps[currentEditStep] //要修改的图形

	//Todo:旋转
	if (editSteps[currentEditStep].type == LINE)	//移动的对象是线条
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色
		CPoint pc = editSteps[currentEditStep].centerPoint;
		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

		p1 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p1);	//位移关键点
		p2 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p2);
		//Todo:重新写入数据
		this->SetLine(p1, p2, color, currentEditStep);	//重新绘制

	}

	else if (editSteps[currentEditStep].type == CIRCLE)	//移动的对象是线条
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色
		CPoint pc = editSteps[currentEditStep].centerPoint;
		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

		p1 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p1);	//位移关键点
		p2 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p2);
		//Todo:重新写入数据
		this->SetCircle(p1, p2, color, currentEditStep);	//重新绘制

	}
	else if (editSteps[currentEditStep].type == RECT)	//移动的对象是线条
	{
		COLORREF color = editSteps[currentEditStep].point.color;	//获取颜色
		CPoint pc = editSteps[currentEditStep].centerPoint;
		CPoint p1 = CPoint(editSteps[currentEditStep].point.x, editSteps[currentEditStep].point.y);	//获取关键点
		CPoint p2 = CPoint(editSteps[currentEditStep].point.next->x, editSteps[currentEditStep].point.next->y);

		p1 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p1);	//位移关键点
		p2 = MyTransform::myglRotatef(angle, pc.x, pc.y, &p2);
		//Todo:重新写入数据
		this->SetRect(p1, p2, color, currentEditStep);	//重新绘制

	}

	//Todo:刷新屏幕
	Invalidate();


}
