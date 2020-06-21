#pragma once


// RotateDialog 对话框

class RotateDialog : public CDialogEx
{
	DECLARE_DYNAMIC(RotateDialog)

public:
	RotateDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RotateDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
public:
	float angle;
	int RotateX;
	int RotateY;
	bool isCenter = true;
	bool isRotate = false;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
