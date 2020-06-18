#pragma once
#include <afxwin.h>
#include <afxwin.h>
#include <gl/gl.h>
#include <gl/glu.h>
class COpenGLControl :
    public CWnd
{

public:
    /******************/
    /* PUBLIC MEMBERS */
    /******************/
    // Timer
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
   /* COpenGLControl();
    void oglCreate(CRect rect, CWnd* parent);
    void oglInitialize(void);
    void oglDrawLineCube(void);
    void oglDrawCube(void);
    void oglDrawLineSphere(void);
    void oglDrawSphere(void);
    void oglDrawFourFace(void);*/
};

