
// MyCadView.h: CMyCadView 类的接口
//

#pragma once
#define MAXEDITNUM 1000;

class CMyCadView : public CView
{
protected: // 仅从序列化创建
	CMyCadView() noexcept;
	DECLARE_DYNCREATE(CMyCadView)

// 特性
public:
	CMyCadDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyCadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()


public:
	struct Points	//保存像素点链表
	{
		int x, y;	//像素点位置
		COLORREF color;	//像素点颜色
		Points * next;
	};

	typedef struct EditStep		//操作步骤
	{
		int step;		//第step步
		CPoint centerPoint;	//图形中心点
		Points  point;	//当前操作步骤链表头节点
	}*pEditStep;




	int currentStep = 0;	//当前操作步骤

	EditStep editStep[1000];//操作记录，保存1000条操作记录
	CPoint beginPoint, endPoint;	//开始绘制点和结束绘制点
	COLORREF currentColor = RGB(0,0,0);	//当前选择颜色，默认黑色
	void SetEditStepPoint(int step, int x, int y, COLORREF color);	//设置像素点到editStep中
	void DrawPoints(CDC *pDC);	//绘制点

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MyCadView.cpp 中的调试版本
inline CMyCadDoc* CMyCadView::GetDocument() const
   { return reinterpret_cast<CMyCadDoc*>(m_pDocument); }
#endif

