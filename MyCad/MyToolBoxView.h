#pragma once
#include <afxdockablepane.h>
#include"ToolDialog.h"

class MyToolBoxView :
	public CDockablePane
{
public:
	ToolDialog m_toolDialog;

	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);


	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();

	
};

