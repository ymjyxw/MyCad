#pragma once
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
};
