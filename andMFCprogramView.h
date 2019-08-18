
// andMFCprogramView.h : CandMFCprogramView 类的接口
//

#pragma once

#include "allUtil/OpenGL.h"

class CandMFCprogramView : public CView
{
protected: // 仅从序列化创建
	CandMFCprogramView();
	DECLARE_DYNCREATE(CandMFCprogramView)

// 特性
public:
	CandMFCprogramDoc* GetDocument() const;

// 操作
public:
	virtual void OnInitialUpdate(); // called first time after construct

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CandMFCprogramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	COpenGL opengl;
	float m_yAngle;
	float m_xAngle;
	float m_zAngle;
	float m_xPos;
	float m_yPos;
	float m_zPos;
	CPoint m_MouseDownPoint;
	float m_Scale;

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnDestroy();
	//afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	//afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	//afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // andMFCprogramView.cpp 中的调试版本
inline CandMFCprogramDoc* CandMFCprogramView::GetDocument() const
   { return reinterpret_cast<CandMFCprogramDoc*>(m_pDocument); }
#endif

