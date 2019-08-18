
#include "OpenGL.h"

#include <math.h>

COpenGL::COpenGL(void)
{
	m_xPos = 0.0f;
	m_yPos = 0.0f;
	m_zPos = 0.0f;
	m_xAngle = 0.0f;
	m_yAngle = 0.0f;
	m_zAngle = 0.0f;
	m_Scale = 1.0f;
}


COpenGL::~COpenGL(void)
{
    wglMakeCurrent(hDC, NULL);
    wglDeleteContext(hRC);
}


void COpenGL::Init(void)
{  
    //��������硰�������̽�⡱�Ȼ�ͼ�������ô���

#if 0 
	GLfloat LightPosition[] = {5.0f, 5.0f, 0.0f, 1.0f}; //��Դλ��
	GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f}; //���������
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //��������

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient); //���û�����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse); //���������
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition); //���ù�Դλ��
	glEnable(GL_LIGHT1); //����1�Ź�Դ
	glEnable(GL_LIGHTING); //������Դ
#endif
#if 0
//���뿪��3�����ò������Դ
    GLfloat ambient[] = { 0.4, 0.6, 0.2, 1.0 };
    GLfloat position[] = { 0.0, 1.0, 3.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.2, 0.4, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 60.0 };
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
#endif
}


bool COpenGL::SetupPixelFormat(HDC hdc)
{
    hDC=hdc;

    PIXELFORMATDESCRIPTOR pfd = 
    {
       sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С
       1,                                // �汾��
       PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ
       PFD_SUPPORT_OPENGL |              // ֧��OpenGL
       PFD_DOUBLEBUFFER,                 // ˫����ģʽ
       PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ
       24,                               // 24 λ��ɫ���
       0, 0, 0, 0, 0, 0,                 // ������ɫλ
       0,                                // û�з�͸���Ȼ���
       0,                                // ������λλ
       0,                                // ���ۼӻ���
       0, 0, 0, 0,                       // �����ۼ�λ
       32,                               // 32 λ��Ȼ���   
       0,                                // ��ģ�建��
       0,                                // �޸�������
       PFD_MAIN_PLANE,                   // ����
       0,                                // ����
       0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ
    };

    int nPixelFormat;    // ���ص��ʽ
    if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
    { 
        MessageBox(NULL,L"can not find proper mode",L"Error",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    SetPixelFormat(hDC,nPixelFormat,&pfd);
    hRC = wglCreateContext(hDC);    //����GDI��ͼ��ʹ�õ�HDC������Ӧ��HGLRC
    wglMakeCurrent(hDC, hRC);        //ʹOpenGL��ͼ��ʹ�õ�HGLRCΪ��ǰ��ͼ����

    return TRUE;
}

#define PI 3.14159265358979323846

//��������Ϊ��x��y��z������İ뾶Ϊradius��M��N�ֱ��ʾ����ĺ����򱻷ֳɶ��ٷ�
void drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N)
{
 float step_z = PI/M;
 float step_xy = 2*PI/N;
 float x[4],y[4],z[4];
 
 float angle_z = 0.0;
 float angle_xy = 0.0;
 int i=0, j=0;
 glBegin(GL_QUADS);
  for(i=0; i<M; i++)
  {
   angle_z = i * step_z;
   
   for(j=0; j<N; j++)
   {
    angle_xy = j * step_xy;
 
    x[0] = radius * sin(angle_z) * cos(angle_xy);
    y[0] = radius * sin(angle_z) * sin(angle_xy);
    z[0] = radius * cos(angle_z);
 
    x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
    y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
    z[1] = radius * cos(angle_z + step_z);
 
    x[2] = radius * sin(angle_z + step_z) * cos(angle_xy + step_xy);
    y[2] = radius * sin(angle_z + step_z) * sin(angle_xy + step_xy);
    z[2] = radius * cos(angle_z + step_z);
 
    x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
    y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
    z[3] = radius * cos(angle_z);
 
		for(int k=0; k<4; k++)
		{

			float rangeCol = (zz+z[k] + 1) / 2;
			glColor3f(rangeCol, 1.0 - rangeCol, 0.0);
			
			glVertex3f(xx+x[k], yy+y[k], zz+z[k]);
		}
   }
  }
 glEnd();
}

void COpenGL::Render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);        
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	glTranslatef(m_xPos, m_yPos, m_zPos);
	glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);
	glScalef(m_Scale, m_Scale, m_Scale);

#if 0
    //���Ʋ�����
    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);//���͹�����
        glVertex3f(0.5f,0.5f ,0.0f);
        glVertex3f(0.5f,-0.5f, 0.0f);
        glVertex3f(-0.5f,-0.5f,0.0f);
        glVertex3f(-0.5f,0.5f,0.0f);
    glEnd();
#endif
#if 0
    glBegin(GL_POLYGON);//���������
	    glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.75f, -0.75f, 0.0f);
		glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.75f, -0.75f, 0.0f);
		glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0f, 0.75f, 0.0f);
    glEnd();
#endif

	drawSphere(0.0, 0.0, 0.0, 1.0, 180, 360);

    glFlush();
    SwapBuffers(hDC);
}


void COpenGL::Reshape(int width,int height)
{
    glViewport(0,0,width,height);

	int cx = width;
	int cy = height;

	 //select the full client area  
	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (cx < cy)
		glOrtho(-2.0, 100.0, -2.0*(GLfloat)cy / (GLfloat)cx, 2.0*(GLfloat)cy / (GLfloat)cx, -2.0, 2.0);
	else
		glOrtho(-2.0*(GLfloat)cx / (GLfloat)cy, 2.0*(GLfloat)cx / (GLfloat)cy, -2.0, 2.0, -2.0, 2.0);
	// switch back to the modelview matrix and clear it  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}