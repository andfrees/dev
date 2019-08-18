

#pragma once

#include "stdafx.h"
#include "glut.h"

class COpenGL
{
private:
	HDC hDC; //GDI��ͼ��ʹ�õĵ��豸�������
	HGLRC hRC; //OpenGL��Ⱦʱʹ�õ���Ⱦ�������

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

	bool SetupPixelFormat(HDC hdc); //�������ظ�ʽΪ�ʺ�OpenGL�ĸ�ʽ
	void Init(void); //��ʼ����Ⱦ���������Ե�����
	void Render(void); //���ƴ���

	void Reshape(int width,int height); //�ı䴰�ڴ�Сʱ���Ӵ����еĲ���
};