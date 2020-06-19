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
    

    class Point { //������
    public:
        Point() {};
        Point(double a, double b, double c) :x(a), y(b), z(c) {};
    public:
        double x;
        double y;
        double z;

        Point getPoint(double u, double v)  //����uvλ�û�ȡ��
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



    float m_fPosX, m_fPosY, m_fZoom, m_fRotX, m_fRotY, m_fLastX, m_fLastY; //�����λ��


  
    float ambientLight[4] = { 0.1f,0.3f,0.8f,1.0f };  //������
    float diffuseLight[4] = { 0.25f,0.25f,0.25f,1.0f }; //ɢ���
    float lightPosition[4] = { 0.0f,0.0f,1.0f,0.0f }; //��Դλ��

    //���ʱ���
    float matAmbient[4] = { 1.0f,1.0f,1.0f,1.0f };
    float matDiff[4] = { 1.0f,1.0f,1.0f,1.0f };

   


public:
    ModelShape current_model = LINECUBE;    //Ĭ����ʾ�߿򳤷���ģ��
    float scale_x = 1.0f;  //ģ�ʹ�С
    float scale_y = 1.0f;  //ģ�ʹ�С
    float scale_z = 1.0f;  //ģ�ʹ�С
    float scale_r = 1.0f;  //ģ�ʹ�С
    COLORREF color = RGB(0,100,200); //ģ����ɫ
    bool showBackFace = true; //Ĭ�ϲ�������������

    COpenGLControl();
    void oglCreate(CRect rect, CWnd* parent);   //����OpenGL����
    void oglInitialize(void);   //��ʼ��OpenGL
    void oglDrawLineCube(void); //�����߿򳤷���
    void oglDrawCube(void); //����������
    void oglDrawLineSphere(void); //�����߿�����
    void oglDrawSphere(void); //��������


   
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnDraw(CDC* pDC);

};

