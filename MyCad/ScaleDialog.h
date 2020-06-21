#pragma once


// ScaleDialog 对话框

class ScaleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ScaleDialog)

public:
	ScaleDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ScaleDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	float ScaleX;
	float ScaleY;
	bool IsScale = false;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
