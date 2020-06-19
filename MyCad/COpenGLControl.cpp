#include "pch.h"
#include "COpenGLControl.h"

COpenGLControl::COpenGLControl()
{
	m_fPosX = 0.0f;    // �����λ��
	m_fPosY = 0.0f;
	m_fZoom = 10.0f;   // ��������
	m_fRotX = 0.0f;    // ���������
	m_fRotY = 0.0f;
	m_fLastX = 1.0f;    //�ӽǴ�Сֵ
	m_fLastY = 1.0f;
}

//����Opengl
void COpenGLControl::oglCreate(CRect rect, CWnd* parent)
{
	CString className = AfxRegisterWndClass(CS_HREDRAW |
		CS_VREDRAW | CS_OWNDC, NULL,
		(HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	CreateEx(0, className, "OpenGL", WS_CHILD | WS_VISIBLE |
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

	// ���ô��ڴ�С
	m_oldWindow = rect;
	m_originalRect = rect;

	hWnd = parent;
}

//��ʼ��Opengl
void COpenGLControl::oglInitialize(void)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
	   sizeof(PIXELFORMATDESCRIPTOR),
	   1,
	   PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
	   PFD_TYPE_RGBA,
	   32,    // λ���
	   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	   16,    // z-buffer���
	   0, 0, 0, 0, 0, 0, 0,
	};

	// ��ȡ�����豸
	hdc = GetDC()->m_hDC;

	// ���ظ�ʽ����
	m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, m_nPixelFormat, &pfd);

	//����OpenGL��Ⱦ����
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	//OPenGL��������

	// ���ñ�����ɫ
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);

	

	glFrontFace(GL_CCW); //�������ʱ�뷽��Ϊ����
	glCullFace(GL_BACK);


	glEnable(GL_DEPTH_TEST);//�޳�������
	glDepthFunc(GL_LEQUAL); // �������ֵ



	glShadeModel(GL_SMOOTH);     //ʹ��ƽ����������

	glEnable(GL_CULL_FACE);      //���������α���

	glEnable(GL_LIGHTING);      //���ù���

	//ΪLIGHT0��������
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);

	//���ڿ�ʼ��ЭLIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //���û��������
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); //����ɢ������
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); //���ù�Դ�ڳ����е�λ��

	//���ù�
	glEnable(GL_LIGHT0);
	//glDisable(GL_LIGHT0);

	// Send draw request
	OnDraw(NULL);
}


//�����߿򳤷���
void COpenGLControl::oglDrawLineCube(void)
{
	// �߿�ģʽ
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//������ɫ
	float r, g, b;
	r = GetRValue(color) / 255.0f;
	g = GetGValue(color) / 255.0f;
	b = GetBValue(color) / 255.0f;


	ambientLight[0] = r;  //������
	ambientLight[1] = g;  //������
	ambientLight[2] = b;  //������
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //���û��������


	glBegin(GL_QUADS); //������


	
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

//���Ƴ�����
void COpenGLControl::oglDrawCube(void)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glPushMatrix();
	//������ɫ
	float r, g, b;
	r = GetRValue(color)/255.0f;
	g = GetGValue(color)/255.0f;
	b = GetBValue(color)/255.0f;


	ambientLight[0] = r;  //������
	ambientLight[1] = g;  //������
	ambientLight[2] = b;  //������
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //���û��������

	glBegin(GL_QUADS);    //����
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(scale_x, scale_y, scale_z);
	glVertex3f(scale_x, scale_y, -scale_z);
	glVertex3f(-scale_x, scale_y, -scale_z);
	glVertex3f(-scale_x, scale_y, scale_z);
	glEnd();
	glBegin(GL_QUADS);    //����
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(scale_x, -scale_y, scale_z);
	glVertex3f(-scale_x, -scale_y, scale_z);
	glVertex3f(-scale_x, -scale_y, -scale_z);
	glVertex3f(scale_x, -scale_y, -scale_z);
	glEnd();
	glBegin(GL_QUADS);    //ǰ��
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(scale_x, scale_y, scale_z);
	glVertex3f(-scale_x, scale_y, scale_z);
	glVertex3f(-scale_x, -scale_y, scale_z);
	glVertex3f(scale_x, -scale_y, scale_z);
	glEnd();
	glBegin(GL_QUADS);    //����
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(scale_x, scale_y, -scale_z);
	glVertex3f(scale_x, -scale_y, -scale_z);
	glVertex3f(-scale_x, -scale_y, -scale_z);
	glVertex3f(-scale_x, scale_y, -scale_z);
	glEnd();
	glBegin(GL_QUADS);    //����
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-scale_x, scale_y, scale_z);
	glVertex3f(-scale_x, scale_y, -scale_z);
	glVertex3f(-scale_x, -scale_y, -scale_z);
	glVertex3f(-scale_x, -scale_y, scale_z);
	glEnd();
	glBegin(GL_QUADS);    //����
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(scale_x, scale_y, scale_z);
	glVertex3f(scale_x, -scale_y, scale_z);
	glVertex3f(scale_x, -scale_y, -scale_z);
	glVertex3f(scale_x, scale_y, -scale_z);
	glEnd();
	glPopMatrix();


}

//�����߿�����
void COpenGLControl::oglDrawLineSphere(void)
{
	float r, g, b;
	r = GetRValue(color) / 255.0f;
	g = GetGValue(color) / 255.0f;
	b = GetBValue(color) / 255.0f;


	ambientLight[0] = r;  //������
	ambientLight[1] = g;  //������
	ambientLight[2] = b;  //������
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //���û��������

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


	ambientLight[0] = r;  //������
	ambientLight[1] = g;  //������
	ambientLight[2] = b;  //������
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //���û��������

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

	// TODO:  �ڴ������ר�õĴ�������
	oglInitialize();
	return 0;
}


void COpenGLControl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()

	ValidateRect(NULL);
}


void COpenGLControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED) return;

	// ӳ��OpenGL����
	glViewport(0, 0, cx, cy);

	//ͶӰ�ӽ�
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// ���õ�ǰ��ͼ��͸��ͼ
	gluPerspective(35.0f, (float)cx / (float)cy, 0.01f, 2000.0f);

	// ģ���ӽ�
	glMatrixMode(GL_MODELVIEW);
}


void COpenGLControl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
	{
		// �����ɫ����
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (showBackFace)
			glDisable(GL_CULL_FACE);	//�������α���
		else
			glEnable(GL_CULL_FACE);      //���������α���


		


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


	
		// ����������
		SwapBuffers(hdc);

		break;
	}

	default:
		break;
	}


	CWnd::OnTimer(nIDEvent);
}

//�������ӿ�
void COpenGLControl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int diffX = (int)(point.x - m_fLastX);
	int diffY = (int)(point.y - m_fLastY);
	m_fLastX = (float)point.x;
	m_fLastY = (float)point.y;

	// ��������ӵ���ת
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

	// �Ҽ������ӵ�Զ��
	else if (nFlags & MK_RBUTTON)
	{
		m_fZoom -= (float)0.1f * diffY;
	}

	// �м������ӵ�λ��
	else if (nFlags & MK_MBUTTON)
	{
		m_fPosX += (float)0.05f * diffX;
		m_fPosY -= (float)0.05f * diffY;
	}

	OnDraw(NULL);

	CWnd::OnMouseMove(nFlags, point);
}

//�������
void COpenGLControl::OnDraw(CDC* pDC)
{
	

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -m_fZoom);
	glTranslatef(m_fPosX, m_fPosY, 0.0f);
	glRotatef(m_fRotX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fRotY, 0.0f, 1.0f, 0.0f);
}
