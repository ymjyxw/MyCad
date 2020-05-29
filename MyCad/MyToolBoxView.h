#pragma once
#include <afxdockablepane.h>
#include"ToolDialog.h"

class MyToolBoxView :
	public CDockablePane
{
public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	ToolDialog m_toolDialog;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
};

