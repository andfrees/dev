

#pragma once

#include "stdafx.h"
#include "glut.h"

class COpenGL
{
private:
	HDC hDC; //GDI绘图中使用的的设备环境句柄
	HGLRC hRC; //OpenGL渲染时使用的渲染环境句柄

public:
	COpenGL(void);
	virtual ~COpenGL(void);

	GLfloat m_yAngle;
	GLfloat m_xAngle;
	GLfloat m_zAngle;
	GLfloat m_xPos;
	GLfloat m_yPos;
	GLfloat m_zPos;
	float m_Scale;

	bool SetupPixelFormat(HDC hdc); //设置像素格式为适合OpenGL的格式
	void Init(void); //初始化渲染过程中属性的设置
	void Render(void); //绘制代码

	void Reshape(int width,int height); //改变窗口大小时对视窗进行的操作
};