#pragma once


// mirrorDialog 对话框

class mirrorDialog : public CDialogEx
{
	DECLARE_DYNAMIC(mirrorDialog)

public:
	mirrorDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~mirrorDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	int direction = 1;
	bool isMirror = false;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	virtual BOOL OnInitDialog();
};
