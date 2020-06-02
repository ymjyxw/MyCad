﻿#pragma once


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
		MOVEOBJECT,
		ROTATEOBJECT,
		SCALEOBJECT,

	};
	EditModel currentModel = DRAWLINE;	//默认为画线操作
	COLORREF currentColor = RGB(0, 0, 0);	//当前选择颜色，默认黑色
public:
	



	afx_msg void OnDrawLine();
	afx_msg void OnMoveObject();
};
