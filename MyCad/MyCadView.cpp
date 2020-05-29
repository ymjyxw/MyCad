
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyCadView

IMPLEMENT_DYNCREATE(CMyCadView, CView)

BEGIN_MESSAGE_MAP(CMyCadView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
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

void CMyCadView::OnDraw(CDC* /*pDC*/)
{
	CMyCadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMyCadView 打印

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
