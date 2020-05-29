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
};
