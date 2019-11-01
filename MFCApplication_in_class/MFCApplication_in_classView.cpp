
// MFCApplication_in_classView.cpp : implementation of the CMFCApplication_in_classView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication_in_class.h"
#endif

#include "MFCApplication_in_classDoc.h"
#include "MFCApplication_in_classView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication_in_classView

IMPLEMENT_DYNCREATE(CMFCApplication_in_classView, CView)

BEGIN_MESSAGE_MAP(CMFCApplication_in_classView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDC_DIALOG, OnDialog)
	ON_COMMAND(ID_OPENCLOSE_CLOSE, &CMFCApplication_in_classView::OnOpencloseClose)
	ON_COMMAND(ID_OPENCLOSE_OPEN, &CMFCApplication_in_classView::OnOpencloseOpen)
	ON_UPDATE_COMMAND_UI(ID_OPENCLOSE_OPEN, &CMFCApplication_in_classView::OnUpdateOpencloseOpen)
	ON_UPDATE_COMMAND_UI(ID_OPENCLOSE_CLOSE, &CMFCApplication_in_classView::OnUpdateOpencloseClose)
END_MESSAGE_MAP()

// CMFCApplication_in_classView construction/destruction

CMFCApplication_in_classView::CMFCApplication_in_classView()
{
	// TODO: add construction code here

}

CMFCApplication_in_classView::~CMFCApplication_in_classView()
{
}

BOOL CMFCApplication_in_classView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCApplication_in_classView drawing

void CMFCApplication_in_classView::OnDraw(CDC* pDC)
{
	CMFCApplication_in_classDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	int margin;
	int x;
	int y;
	COLORREF color;
	POINT pt;
	CRect rect; // Client rectangle
	GetClientRect(&rect); // 

	margin = dialog.margin;
	color = dialog.color;

	for (x = rect.left + margin; x < rect.right - margin; x++)
	{
		for (y = rect.top + margin; y < rect.bottom - margin; y++)
		{
			pt.x = x;
			pt.y = y;
			pDC->SetPixel(pt, color);
		}
	}

	pDC->DrawText(_T("Hello, MFC"), -1, &rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}


// CMFCApplication_in_classView printing

BOOL CMFCApplication_in_classView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCApplication_in_classView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCApplication_in_classView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCApplication_in_classView::OnDialog()
{
	// TODO: Add your command handler code here
	if (dialog.DoModal() == IDOK) {
		Invalidate();
	}
}

// CMFCApplication_in_classView diagnostics

#ifdef _DEBUG
void CMFCApplication_in_classView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication_in_classView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication_in_classDoc* CMFCApplication_in_classView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication_in_classDoc)));
	return (CMFCApplication_in_classDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication_in_classView message handlers


void CMFCApplication_in_classView::OnOpencloseClose()
{
	// TODO: Add your command handler code here
	open = false;
	Invalidate();
}


void CMFCApplication_in_classView::OnOpencloseOpen()
{
	// TODO: Add your command handler code here
	open = true;
	Invalidate();
}


void CMFCApplication_in_classView::OnUpdateOpencloseOpen(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(open);
}


void CMFCApplication_in_classView::OnUpdateOpencloseClose(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!open);
}
