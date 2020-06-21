#pragma once


// ToolDialog 对话框

class ToolDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ToolDialog)

public:
	ToolDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ToolDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	enum EditModel	//操作样式
	{
		DRAWLINE,
		DRAWCIRCLE,
		DRAWRECT,
		DRAWBEZIER,
		DRAWYUANHU,

		DRAWFILLRECT,
		DRAWFILLCIRCLE,

		MOVEOBJECT,
		ROTATEOBJECT,
		SCALEOBJECT,

		CHANGECOLOR
	};
	EditModel currentModel = DRAWLINE;	//默认为画线操作
	COLORREF currentColor = RGB(0, 0, 0);	//当前选择颜色，默认黑色

public:
	



	afx_msg void OnDrawLine();
	afx_msg void OnMoveObject();
	afx_msg void OnDrawCircle();
	afx_msg void OnRotateObject();
	afx_msg void OnDrawRect();

	afx_msg void OnCreateFillRect();
	afx_msg void OnSetColor();
	
	afx_msg void OnPaint();
	afx_msg void OnDrawFillCircle();
	afx_msg void OnDrawBezier();
	afx_msg void OnDrawYuanHu();
};
