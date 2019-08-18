
// andMFCprogramView.cpp : CandMFCprogramView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "andMFCprogram.h"
#endif

#include "andMFCprogramDoc.h"
#include "andMFCprogramView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CandMFCprogramView

IMPLEMENT_DYNCREATE(CandMFCprogramView, CView)

BEGIN_MESSAGE_MAP(CandMFCprogramView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CandMFCprogramView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CandMFCprogramView 构造/析构

CandMFCprogramView::CandMFCprogramView()
{
	// TODO: 在此处添加构造代码
	m_xPos = 0.0f;
	m_yPos = 0.0f;
	m_zPos = 0.0f;
	m_xAngle = 0.0f;
	m_yAngle = 0.0f;
	m_zAngle = 0.0f;
	m_Scale = 1.0f;
}

CandMFCprogramView::~CandMFCprogramView()
{
}


int CandMFCprogramView::OnCreate(LPCREATESTRUCT lpCreateStruct){

	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC *m_pDC = new CClientDC(this);
	ASSERT(m_pDC != NULL);

	return 0;
}

BOOL CandMFCprogramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	
	cs.style|=WS_CLIPSIBLINGS|WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

void CandMFCprogramView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO: 写入最终选择模式代码之后移除此代码
    // m_pSelection = NULL;    // 初始化所选内容
	opengl.SetupPixelFormat(::GetDC(GetSafeHwnd()));
    opengl.Init();
}


// CandMFCprogramView 绘制

void CandMFCprogramView::OnDraw(CDC* /*pDC*/)
{
	CandMFCprogramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	opengl.m_xPos   = m_xPos;
	opengl.m_yPos   = m_yPos;
	opengl.m_zPos   = m_zPos;
	opengl.m_xAngle = m_xAngle;
	opengl.m_yAngle = m_yAngle;
	opengl.m_zAngle = m_zAngle;
	opengl.m_Scale  = m_Scale;

	opengl.Render();
}


void CandMFCprogramView::OnSize(UINT nType, int cx, int cy)
{

	if (0 >= cx || 0 >= cy)
	{
		return;
	}

    opengl.Reshape(cx,cy);
}

void CandMFCprogramView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
 
	if (GetCapture() == this)
	{
		//Increment the object rotation angles  
		m_xAngle += (point.y - m_MouseDownPoint.y) / 3.6;
		m_yAngle += (point.x - m_MouseDownPoint.x) / 3.6;
		//Redraw the view  
		InvalidateRect(NULL, FALSE);
		//Set the mouse point  
		m_MouseDownPoint = point;
	};
	CView::OnMouseMove(nFlags, point);
}

BOOL CandMFCprogramView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_Scale >= 0)
	{
		m_Scale += 0.05 *zDelta / 120;
	}
	else
	{
		if (zDelta > 0)
		{
			m_Scale += 0.05 *zDelta / 120;
		}
	}
	InvalidateRect(NULL, FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
	
}

void CandMFCprogramView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
 
	m_MouseDownPoint = point;
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}

void CandMFCprogramView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
 
	m_MouseDownPoint = CPoint(0, 0);
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}

void CandMFCprogramView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
 
	switch (nChar)
	{
	case VK_UP:
		m_yPos = m_yPos + 1.0f;
		break;
	case VK_DOWN:
		m_yPos = m_yPos - 1.0f;
		break;
	case VK_LEFT:
		m_xPos = m_xPos - 1.0f;
		break;
	case VK_RIGHT:
		m_xPos = m_xPos + 1.0f;
		break;
	default:
		MessageBox(_T("Press the arrow keys only"));
		break;
	}
 
	InvalidateRect(NULL, FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CandMFCprogramView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CandMFCprogramView::OnDestroy()
{
	// TODO:  在此处添加消息处理程序代码
	
	//Delete the rendering context  
	//::wglMakeCurrent(NULL, NULL);
	//if (m_hglrc)
	//	::wglDeleteContext(m_hglrc);
	//if (m_pDC)
	//	delete m_pDC;

	CView::OnDestroy();
}

// CandMFCprogramView 打印


void CandMFCprogramView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CandMFCprogramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CandMFCprogramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CandMFCprogramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CandMFCprogramView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CandMFCprogramView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CandMFCprogramView 诊断

#ifdef _DEBUG
void CandMFCprogramView::AssertValid() const
{
	CView::AssertValid();
}

void CandMFCprogramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CandMFCprogramDoc* CandMFCprogramView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CandMFCprogramDoc)));
	return (CandMFCprogramDoc*)m_pDocument;
}
#endif //_DEBUG


// CandMFCprogramView 消息处理程序
