
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
    //可添加例如“开启深度探测”等绘图属性设置代码

#if 0 
	GLfloat LightPosition[] = {5.0f, 5.0f, 0.0f, 1.0f}; //光源位置
	GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f}; //环境光参数
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //漫射光参数

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient); //设置环境光
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse); //设置漫射光
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition); //设置光源位置
	glEnable(GL_LIGHT1); //启用1号光源
	glEnable(GL_LIGHTING); //开启光源
#endif
#if 0
//代码开关3：设置材质与光源
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
       sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小
       1,                                // 版本号
       PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图
       PFD_SUPPORT_OPENGL |              // 支持OpenGL
       PFD_DOUBLEBUFFER,                 // 双缓存模式
       PFD_TYPE_RGBA,                    // RGBA 颜色模式
       24,                               // 24 位颜色深度
       0, 0, 0, 0, 0, 0,                 // 忽略颜色位
       0,                                // 没有非透明度缓存
       0,                                // 忽略移位位
       0,                                // 无累加缓存
       0, 0, 0, 0,                       // 忽略累加位
       32,                               // 32 位深度缓存   
       0,                                // 无模板缓存
       0,                                // 无辅助缓存
       PFD_MAIN_PLANE,                   // 主层
       0,                                // 保留
       0, 0, 0                           // 忽略层,可见性和损毁掩模
    };

    int nPixelFormat;    // 像素点格式
    if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
    { 
        MessageBox(NULL,L"can not find proper mode",L"Error",MB_OK|MB_ICONEXCLAMATION);
        return FALSE;
    }

    SetPixelFormat(hDC,nPixelFormat,&pfd);
    hRC = wglCreateContext(hDC);    //利用GDI绘图所使用的HDC创建对应的HGLRC
    wglMakeCurrent(hDC, hRC);        //使OpenGL绘图所使用的HGLRC为当前绘图工具

    return TRUE;
}

#define PI 3.14159265358979323846

//球心坐标为（x，y，z），球的半径为radius，M，N分别表示球体的横纵向被分成多少份
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
    //绘制操作：
    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);//填充凸多边形
        glVertex3f(0.5f,0.5f ,0.0f);
        glVertex3f(0.5f,-0.5f, 0.0f);
        glVertex3f(-0.5f,-0.5f,0.0f);
        glVertex3f(-0.5f,0.5f,0.0f);
    glEnd();
#endif
#if 0
    glBegin(GL_POLYGON);//填充三角形
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