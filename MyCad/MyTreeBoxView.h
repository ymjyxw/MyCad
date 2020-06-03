#pragma once
#include <afxdockablepane.h>
#include "TreeDialog.h"
class MyTreeBoxView :
	public CDockablePane
{
public:
	TreeDialog m_treeDialog;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

