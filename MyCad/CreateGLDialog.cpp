﻿// CreateGLDialog.cpp: 实现文件
//

#include "pch.h"
#include "MyCad.h"
#include "CreateGLDialog.h"
#include "afxdialogex.h"
#include "resource.h"

// CreateGLDialog 对话框

IMPLEMENT_DYNAMIC(CreateGLDialog, CDialogEx)

CreateGLDialog::CreateGLDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	
	//CSliderCtrl* pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	//pSlidCtrl->SetPos(1);
}

CreateGLDialog::~CreateGLDialog()
{
}

void CreateGLDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPENGL, Open_Pic);

	DDX_Control(pDX, IDC_SLIDER1, slider_x);
	DDX_Control(pDX, IDC_SLIDER2, slider_y);
	DDX_Control(pDX, IDC_SLIDER3, slider_z);
	DDX_Control(pDX, IDC_SLIDER4, slider_r);
}


BEGIN_MESSAGE_MAP(CreateGLDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON11, &CreateGLDialog::OnShowBackFace)
	ON_BN_CLICKED(IDC_BUTTON1, &CreateGLDialog::OnChangeColor)
	
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON2, &CreateGLDialog::OnCloseDialog)

	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON3, &CreateGLDialog::OnCreateCube)
	ON_BN_CLICKED(IDC_BUTTON8, &CreateGLDialog::OnCreateLineCube)
	ON_BN_CLICKED(IDC_BUTTON9, &CreateGLDialog::OnCreateSphere)
	ON_BN_CLICKED(IDC_BUTTON10, &CreateGLDialog::OnCreateLineSphere)
	ON_BN_CLICKED(IDC_BUTTON7, &CreateGLDialog::OnExportImage)
END_MESSAGE_MAP()


// CreateGLDialog 消息处理程序


BOOL CreateGLDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;

	//获取照片控制器位置
	//GetDlgItem(IDC_OPENGL)->GetWindowRect(rect);
	Open_Pic.GetWindowRect(rect);

	//转换为屏幕坐标
	ScreenToClient(rect);

	// 创建OPenGL窗口
	m_oglWindow.oglCreate(rect, this);

	// 设置OpenGL窗口渲染时间
	m_oglWindow.m_unpTimer = m_oglWindow.SetTimer(1, 1, 0);

	slider_x.SetPos(1); //设置默认值
	slider_x.SetRange(1, 5); //设置最大值与最小值
	slider_y.SetPos(1); //设置默认值
	slider_y.SetRange(1, 5); //设置最大值与最小值
	slider_z.SetPos(1); //设置默认值
	slider_z.SetRange(1, 5); //设置最大值与最小值
	slider_r.SetPos(1); //设置默认值
	slider_r.SetRange(1, 5); //设置最大值与最小值
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//开启与关闭背面消隐
void CreateGLDialog::OnShowBackFace()
{
	// TODO: 在此添加控件通知处理程序代码
	m_oglWindow.showBackFace = !(m_oglWindow.showBackFace);
}

//改变物体颜色
void CreateGLDialog::OnChangeColor()
{
	// TODO: 在此添加控件通知处理程序代码


	//文字颜色对话框
	CColorDialog cd;

	if (cd.DoModal() == IDOK)
	{
		//获取选中的颜色
		m_oglWindow.color = cd.GetColor();
	
	}

	
}


//关闭窗口
void CreateGLDialog::OnCloseDialog()
{
	// TODO: 在此添加控件通知处理程序代码
	this->EndDialog(-1);
}



//滑条改变物体大小
void CreateGLDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CString str;
	//str.Format("%d", slider_x.GetPos());
	//MessageBox(str);
	//_cprintf("%d\t", slider_x.GetPos());
	m_oglWindow.scale_x = slider_x.GetPos();
	m_oglWindow.scale_y = slider_y.GetPos();
	m_oglWindow.scale_z = slider_z.GetPos();
	m_oglWindow.scale_r = slider_r.GetPos();
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//设置模型
void CreateGLDialog::OnCreateCube()
{
	// TODO: 在此添加控件通知处理程序代码
	m_oglWindow.current_model = COpenGLControl::CUBE;
}

//设置模型
void CreateGLDialog::OnCreateLineCube()
{
	// TODO: 在此添加控件通知处理程序代码
	m_oglWindow.current_model = COpenGLControl::LINECUBE;
}

//设置模型
void CreateGLDialog::OnCreateSphere()
{
	// TODO: 在此添加控件通知处理程序代码
	m_oglWindow.current_model = COpenGLControl::SPHERE;
}

//设置模型
void CreateGLDialog::OnCreateLineSphere()
{
	// TODO: 在此添加控件通知处理程序代码
	m_oglWindow.current_model = COpenGLControl::LINESPHERE;
}

//导出图片
void CreateGLDialog::OnExportImage()
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rect;
	Open_Pic.GetWindowRect(rect);

	//转换为屏幕坐标
	ScreenToClient(rect);
	
	CClientDC dc(this);
	
	HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);	//创建兼容位图
	HDC hdc = CreateCompatibleDC(dc);      //创建兼容DC，以便将图像保存为不同的格式
	HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);	//将位图选入DC，并保存返回值 
	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);	//将屏幕DC的图像复制到内存DC中


	CImage image;
	image.Attach(hbitmap);                //将位图转化为一般图像

	CString  strFilter = _T("图片文件(*.jpg)|*.jpg||");
	CFileDialog dlg(FALSE, _T("jpg"), _T("MyCadGLImage"), NULL, strFilter);

	if (dlg.DoModal() != IDOK)	//模态窗口显示
		return;

	CString strFileName;          //文件路径


	strFileName = dlg.m_ofn.lpstrFile;


	HRESULT hResult = image.Save(strFileName);     //保存图像

	if (FAILED(hResult))
		MessageBox(_T("保存图像文件失败！"));
	else
		MessageBox(_T("图像保存成功！"));

	image.Detach();
	SelectObject(hdc, hOldMap);

}
