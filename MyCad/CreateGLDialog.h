#pragma once
#include "COpenGLControl.h"
#include "COpenGLControl.h"
// CreateGLDialog 对话框

class CreateGLDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CreateGLDialog)

public:
	CreateGLDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CreateGLDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

public:
	COpenGLControl m_oglWindow; //OpenGL窗口控制器

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic Open_Pic;	//OpenGL窗口
	afx_msg void OnShowBackFace();
	afx_msg void OnChangeColor();
	
	

	afx_msg void OnCloseDialog();

	
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl slider_x;
	CSliderCtrl slider_y;
	CSliderCtrl slider_z;
	afx_msg void OnCreateCube();
	afx_msg void OnCreateLineCube();
	afx_msg void OnCreateSphere();
	afx_msg void OnCreateLineSphere();
};
