#pragma once

// TreeDialog 对话框

class TreeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(TreeDialog)

public:
	TreeDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~TreeDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TREEDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int tree_currentStep=-1; //代表没有选择任何一个图形
	void SetTreeItem(CString str);
	void DelTreeItem();//删除Item

private:
	int ItemCount = 0; //当前绘制图形的数量
	CTreeCtrl m_treeCtrl;
	HTREEITEM hRoot;     // 树的根节点的句柄   
	HTREEITEM hCataItem[1000]; // 可表示任一分类节点的句柄   

	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	int ChangeStep(); //改变当前图形
};
