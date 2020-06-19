#pragma once
#include <afxwin.h>
#include <afxwin.h>
#include <gl/gl.h>
#include <gl/glu.h>
#define PI 3.1415926
class COpenGLControl :
    public CWnd
{
    
public:
    /******************/
    /* PUBLIC MEMBERS */
    /******************/
    // Timer
    

    class Point { //内置类
    public:
        Point() {};
        Point(double a, double b, double c) :x(a), y(b), z(c) {};
    public:
        double x;
        double y;
        double z;

        Point getPoint(double u, double v)  //根据uv位置获取点
        {
            double x = sin(PI * v) * cos(PI * 2 * u);
            double y = sin(PI * v) * sin(PI * 2 * u);
            double z = cos(PI * v);
            return Point(x, y, z);
        }
        

    };

    enum ModelShape{
        LINECUBE,
        CUBE,
        LINESPHERE,
        SPHERE
    };

    UINT_PTR m_unpTimer;


private:
    /*******************/
    /* PRIVATE MEMBERS */
    /*******************/
    // Window information
    CWnd* hWnd;
    HDC     hdc;
    HGLRC   hrc;
    int     m_nPixelFormat;
    CRect   m_rect;
    CRect   m_oldWindow;
    CRect   m_originalRect;



    float m_fPosX, m_fPosY, m_fZoom, m_fRotX, m_fRotY, m_fLastX, m_fLastY; //摄像机位置


  
    float ambientLight[4] = { 0.1f,0.3f,0.8f,1.0f };  //环境光
    float diffuseLight[4] = { 0.25f,0.25f,0.25f,1.0f }; //散射光
    float lightPosition[4] = { 0.0f,0.0f,1.0f,0.0f }; //光源位置

    //材质变量
    float matAmbient[4] = { 1.0f,1.0f,1.0f,1.0f };
    float matDiff[4] = { 1.0f,1.0f,1.0f,1.0f };

   


public:
    ModelShape current_model = LINECUBE;    //默认显示线框长方体模型
    float scale_x = 1.0f;  //模型大小
    float scale_y = 1.0f;  //模型大小
    float scale_z = 1.0f;  //模型大小
    float scale_r = 1.0f;  //模型大小
    COLORREF color = RGB(0,100,200); //模型颜色
    bool showBackFace = true; //默认不开启背面消隐

    COpenGLControl();
    void oglCreate(CRect rect, CWnd* parent);   //创建OpenGL窗口
    void oglInitialize(void);   //初始化OpenGL
    void oglDrawLineCube(void); //绘制线框长方体
    void oglDrawCube(void); //创建长方体
    void oglDrawLineSphere(void); //创建线框球体
    void oglDrawSphere(void); //创建球体


   
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnDraw(CDC* pDC);

};

