#include "pch.h"
#include "COpenGLControl.h"

COpenGLControl::COpenGLControl()
{
	m_fPosX = 0.0f;    // 摄像机位置
	m_fPosY = 0.0f;
	m_fZoom = 10.0f;   // 摄像机深度
	m_fRotX = 0.0f;    // 摄像机方向
	m_fRotY = 0.0f;
	m_fLastX = 1.0f;    //视角大小值
	m_fLastY = 1.0f;
}

//创建Opengl
void COpenGLControl::oglCreate(CRect rect, CWnd* parent)
{
	CString className = AfxRegisterWndClass(CS_HREDRAW |
		CS_VREDRAW | CS_OWNDC, NULL,
		(HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	CreateEx(0, className, "OpenGL", WS_CHILD | WS_VISIBLE |
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

	// 设置窗口大小
	m_oldWindow = rect;
	m_originalRect = rect;

	hWnd = parent;
}

//初始化Opengl
void COpenGLControl::oglInitialize(void)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
	   sizeof(PIXELFORMATDESCRIPTOR),
	   1,
	   PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
	   PFD_TYPE_RGBA,
	   32,    // 位深度
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   16,    // z-buffer深度
	   0, 0, 0, 0, 0, 0, 0,
	};

	// 获取绘制设备
	hdc = GetDC()->m_hDC;

	// 像素格式设置
	m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, m_nPixelFormat, &pfd);

	//设置OpenGL渲染环境
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	//OPenGL基础设置

	// 设置背景颜色
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);

	

	glFrontFace(GL_CCW); //多边形逆时针方向为正面
	glCullFace(GL_BACK);


	glEnable(GL_DEPTH_TEST);//剔除隐藏面
	glDepthFunc(GL_LEQUAL); // 设置深度值



	glShadeModel(GL_SMOOTH);     //使用平滑明暗处理

	glEnable(GL_CULL_FACE);      //不计算多边形背面

	glEnable(GL_LIGHTING);      //启用光照

	//为LIGHT0设置析质
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);

	//现在开始调协LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //设置环境光分量
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); //设置散射光分量
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); //设置光源在场景中的位置

	//启用光
	glEnable(GL_LIGHT0);
	//glDisable(GL_LIGHT0);

	// Send draw request
	OnDraw(NULL);
}


//绘制线框长方体
void COpenGLControl::oglDrawLineCube(void)
{
	// 线框模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//设置颜色
	float r, g, b;
	r = GetRValue(color) / 255.0f;
	g = GetGValue(color) / 255.0f;
	b = GetBValue(color) / 255.0f;


	ambientLight[0] = r;  //环境光
	ambientLight[1] = g;  //环境光
	ambientLight[2] = b;  //环境光
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //设置环境光分量


	glBegin(GL_QUADS); //长方体


	
	// Top Side
	glVertex3f(scale_x, scale_y, scale_z);
	glVertex3f(scale_x, scale_y, -scale_z);
	glVertex3f(-scale_x, scale_y, -scale_z);
	glVertex3f(-scale_x, scale_y, scale_z);

	// Bottom Side
	
	glVertex3f(-scale_x, -scale_y, -scale_z);
	glVertex3f(scale_x, -scale_y, -scale_z);
	glVertex3f(scale_x, -scale_y, scale_z);
	glVertex3f(-scale_x, -scale_y, scale_z);

	// Front Side
	glVertex3f(scale_x, scale_y, scale_z);
	glVertex3f(-scale_x, scale_y, scale_z);
	glVertex3f(-scale_x, -scale_y, scale_z);
	glVertex3f(scale_x, -scale_y, scale_z);

	// Back Side
	glVertex3f(-scale_x, -scale_y, -scale_z);
	glVertex3f(-scale_x, scale_y, -scale_z);
	glVertex3f(scale_x, scale_y, -scale_z);
	glVertex3f(scale_x, -scale_y, -scale_z);

	// Left Side
	glVertex3f(-scale_x, -scale_y, -scale_z);
	glVertex3f(-scale_x, -scale_y, scale_z);
	glVertex3f(-scale_x, scale_y, scale_z);
	glVertex3f(-scale_x, scale_y, -scale_z);

	// Right Side
	glVertex3f(scale_x, scale_y, scale_z);
	glVertex3f(scale_x, -scale_y, scale_z);
	glVertex3f(scale_x, -scale_y, -scale_z);
	glVertex3f(scale_x, scale_y, -scale_z);
	glEnd();
}

//绘制长方体
void COpenGLControl::oglDrawCube(void)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glPushMatrix();
	//设置颜色
	float r, g, b;
	r = GetRValue(color)/255.0f;
	g = GetGValue(color)/255.0f;
	b = GetBValue(color)/255.0f;


	ambientLight[0] = r;  //环境光
	ambientLight[1] = g;  //环境光
	ambientLight[2] = b;  //环境光
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //设置环境光分量

	glBegin(GL_QUADS);    //顶面
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(scale_x, scale_y, scale_z);
	glVertex3f(scale_x, scale_y, -scale_z);
	glVertex3f(-scale_x, scale_y, -scale_z);
	glVertex3f(-scale_x, scale_y, scale_z);
	glEnd();
	glBegin(GL_QUADS);    //底面
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(scale_x, -scale_y, scale_z);
	glVertex3f(-scale_x, -scale_y, scale_z);
	glVertex3f(-scale_x, -scale_y, -scale_z);
	glVertex3f(scale_x, -scale_y, -scale_z);
	glEnd();
	glBegin(GL_QUADS);    //前面
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(scale_x, scale_y, scale_z);
	glVertex3f(-scale_x, scale_y, scale_z);
	glVertex3f(-scale_x, -scale_y, scale_z);
	glVertex3f(scale_x, -scale_y, scale_z);
	glEnd();
	glBegin(GL_QUADS);    //背面
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(scale_x, scale_y, -scale_z);
	glVertex3f(scale_x, -scale_y, -scale_z);
	glVertex3f(-scale_x, -scale_y, -scale_z);
	glVertex3f(-scale_x, scale_y, -scale_z);
	glEnd();
	glBegin(GL_QUADS);    //左面
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-scale_x, scale_y, scale_z);
	glVertex3f(-scale_x, scale_y, -scale_z);
	glVertex3f(-scale_x, -scale_y, -scale_z);
	glVertex3f(-scale_x, -scale_y, scale_z);
	glEnd();
	glBegin(GL_QUADS);    //右面
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(scale_x, scale_y, scale_z);
	glVertex3f(scale_x, -scale_y, scale_z);
	glVertex3f(scale_x, -scale_y, -scale_z);
	glVertex3f(scale_x, scale_y, -scale_z);
	glEnd();
	glPopMatrix();


}

//绘制线框球体
void COpenGLControl::oglDrawLineSphere(void)
{
	float r, g, b;
	r = GetRValue(color) / 255.0f;
	g = GetGValue(color) / 255.0f;
	b = GetBValue(color) / 255.0f;


	ambientLight[0] = r;  //环境光
	ambientLight[1] = g;  //环境光
	ambientLight[2] = b;  //环境光
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //设置环境光分量

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	GLUquadric *qobj = gluNewQuadric();

	gluSphere(qobj, scale_r, 10, 10);
}

void COpenGLControl::oglDrawSphere(void)
{

	float r, g, b;
	r = GetRValue(color) / 255.0f;
	g = GetGValue(color) / 255.0f;
	b = GetBValue(color) / 255.0f;


	ambientLight[0] = r;  //环境光
	ambientLight[1] = g;  //环境光
	ambientLight[2] = b;  //环境光
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //设置环境光分量

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	GLUquadric* qobj = gluNewQuadric();

	gluSphere(qobj, scale_r, 10, 10);
}




BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	oglInitialize();
	return 0;
}


void COpenGLControl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CWnd::OnPaint()

	ValidateRect(NULL);
}


void COpenGLControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED) return;

	// 映射OpenGL坐标
	glViewport(0, 0, cx, cy);

	//投影视角
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// 设置当前视图的透视图
	gluPerspective(35.0f, (float)cx / (float)cy, 0.01f, 2000.0f);

	// 模型视角
	glMatrixMode(GL_MODELVIEW);
}


void COpenGLControl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
	{
		// 清除颜色缓存
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (showBackFace)
			glDisable(GL_CULL_FACE);	//计算多边形背面
		else
			glEnable(GL_CULL_FACE);      //不计算多边形背面


		


		if (current_model == LINECUBE)
			oglDrawLineCube();
		else if (current_model == CUBE)
			oglDrawCube();
		else if(current_model == LINESPHERE)
			oglDrawLineSphere();
		else if(current_model == SPHERE)
			oglDrawSphere();
		//oglDrawFourFace();
	   // GLUquadric *qobj = gluNewQuadric();

		//gluSphere(qobj, 2, 10, 10);


		//gluCylinder(qobj, 0.7, 0.7, 2, 26, 13);


	
		// 交换缓冲区
		SwapBuffers(hdc);

		break;
	}

	default:
		break;
	}


	CWnd::OnTimer(nIDEvent);
}

//鼠标控制视口
void COpenGLControl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int diffX = (int)(point.x - m_fLastX);
	int diffY = (int)(point.y - m_fLastY);
	m_fLastX = (float)point.x;
	m_fLastY = (float)point.y;

	// 左键控制视点旋转
	if (nFlags & MK_LBUTTON)
	{
		m_fRotX += (float)0.5f * diffY;

		if ((m_fRotX > 360.0f) || (m_fRotX < -360.0f))
		{
			m_fRotX = 0.0f;
		}

		m_fRotY += (float)0.5f * diffX;

		if ((m_fRotY > 360.0f) || (m_fRotY < -360.0f))
		{
			m_fRotY = 0.0f;
		}
	}

	// 右键控制视点远近
	else if (nFlags & MK_RBUTTON)
	{
		m_fZoom -= (float)0.1f * diffY;
	}

	// 中键控制视点位置
	else if (nFlags & MK_MBUTTON)
	{
		m_fPosX += (float)0.05f * diffX;
		m_fPosY -= (float)0.05f * diffY;
	}

	OnDraw(NULL);

	CWnd::OnMouseMove(nFlags, point);
}

//相机控制
void COpenGLControl::OnDraw(CDC* pDC)
{
	

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -m_fZoom);
	glTranslatef(m_fPosX, m_fPosY, 0.0f);
	glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);
}
