// TreeDialog.cpp: 实现文件
//

#include "pch.h"
#include "MyCad.h"
#include "TreeDialog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MyCadView.h"
// TreeDialog 对话框

IMPLEMENT_DYNAMIC(TreeDialog, CDialogEx)

TreeDialog::TreeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TREEDIALOG, pParent)
{
}


TreeDialog::~TreeDialog()
{
}

void TreeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_treeCtrl);
}

void TreeDialog::SetTreeItem(CString str)
{

	hCataItem[ItemCount] = m_treeCtrl.InsertItem(str, 1, ItemCount+1, hRoot, TVI_LAST);
	m_treeCtrl.SetItemData(hCataItem[ItemCount], ItemCount+1);

	ItemCount++;
	m_treeCtrl.Expand(hRoot, TVE_EXPAND);	//默认全部展开
}

void TreeDialog::DelTreeItem()
{
	m_treeCtrl.DeleteItem(hCataItem[ItemCount-1]);
	ItemCount--;

}

void TreeDialog::DelAllTreeItem()
{
	tree_currentStep = -1;
	while (ItemCount > 0)
	{
		m_treeCtrl.DeleteItem(hCataItem[ItemCount - 1]);
		ItemCount--;
	}
	
}

int TreeDialog::ChangeStep()
{
	if (ItemCount == 0)	//还没创建子项目直接退出
		return -1;

	HTREEITEM hItem_search = hCataItem[0];
	HTREEITEM hItem = m_treeCtrl.GetSelectedItem();

	int count = 0;
	while (hItem_search&&count<ItemCount)	//获取选中的Item编号
	{
		if (m_treeCtrl.GetItemText(hItem_search) == m_treeCtrl.GetItemText(hItem))
		{
			break;
		}
		hItem_search = m_treeCtrl.GetNextItem(hItem_search, 1);
		count++;
	}

	if (!hItem_search)
		count = -1;
	return count;
}



BEGIN_MESSAGE_MAP(TreeDialog, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &TreeDialog::OnTvnSelchangedTree1)
END_MESSAGE_MAP()


// TreeDialog 消息处理程序


void TreeDialog::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString strText; // 树节点的标签文本字符串   

  // 获取当前选中节点的句柄   
	HTREEITEM hItem = m_treeCtrl.GetSelectedItem();
	
	
	// 获取选中节点的标签文本字符串   
	strText = m_treeCtrl.GetItemText(hItem);
	// 将字符串显示到编辑框中   
	SetDlgItemText(IDC_EDIT1, strText);
	tree_currentStep = ChangeStep();
	

}


BOOL TreeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	hRoot = m_treeCtrl.InsertItem(_T("操作列表"), 0, 0); //添加Root节点
	
	//
	//SetTreeItem(_T("操作1——绘制直线"));
	//SetTreeItem(_T("操作2——绘制直线"));
	//SetTreeItem(_T("操作3——绘制直线"));

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




