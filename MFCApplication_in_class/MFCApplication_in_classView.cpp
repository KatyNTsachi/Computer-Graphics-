
// MFCApplication_in_classView.cpp : implementation of the CMFCApplication_in_classView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication_in_class.h"
#endif
using namespace std;
 
#include <sstream>
#include <iostream>
#include <string.h>

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
	ON_COMMAND(IDC_DIALOG, &CMFCApplication_in_classView::OnDialog)
	ON_COMMAND(ID_OPENCLOSE_CLOSE, &CMFCApplication_in_classView::OnOpencloseClose)
	ON_COMMAND(ID_OPENCLOSE_OPEN, &CMFCApplication_in_classView::OnOpencloseOpen)
	ON_UPDATE_COMMAND_UI(ID_OPENCLOSE_OPEN, &CMFCApplication_in_classView::OnUpdateOpencloseOpen)
	ON_UPDATE_COMMAND_UI(ID_OPENCLOSE_CLOSE, &CMFCApplication_in_classView::OnUpdateOpencloseClose)
	
	ON_COMMAND(ID_MODE_VALUES, &CMFCApplication_in_classView::OnOpenValues)
	ON_COMMAND(ID_MODE_ZEROS, &CMFCApplication_in_classView::OnOpenZeros)
	ON_UPDATE_COMMAND_UI(ID_MODE_VALUES, &CMFCApplication_in_classView::OnUpdateValues)
	ON_UPDATE_COMMAND_UI(ID_MODE_ZEROS, &CMFCApplication_in_classView::OnUpdateZeros)
	
	ON_COMMAND(ID_COLOR_1, &CMFCApplication_in_classView::setColor1)
	ON_COMMAND(ID_COLOR_2, &CMFCApplication_in_classView::setColor2)


	
END_MESSAGE_MAP()

// CMFCApplication_in_classView construction/destruction



CMFCApplication_in_classView::CMFCApplication_in_classView()
{
	postWindowCreate = true;
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

	if (postWindowCreate) 
	{
		postWindowCreate = false;
		initializeDefaultValuesOfFunk();
	}


	// TODO: add draw code for native data here

	CRect rect; // Client rectangle
	GetClientRect(&rect); 
	POINT pt;
	int x, y;
	COLORREF color;
	double funcValue;


	/*
	std::string  s = std::to_string(a);
	std::wstring widestr = std::wstring(s.begin(), s.end());
	const wchar_t *c = widestr.c_str();
	AfxMessageBox(c, MB_OK);
	*/

	my_fun.w = (rect.right - rect.left );
	my_fun.h = (rect.bottom - rect.top );

	for (x = rect.left ; x < rect.right ; x++)
	{
		for (y = rect.top ; y < rect.bottom ; y++)
		{
			pt.x = x;
			pt.y = y;
			
			funcValue = my_fun.getValue(x, y);
			color = my_color.getColorForPixel(funcValue);

			pDC->SetPixel(pt, color);
		}
	}

}

void CMFCApplication_in_classView::initializeDefaultValuesOfFunk()
{
	CRect rect; // Client rectangle
	GetClientRect(&rect);

	my_fun.w = (rect.right - rect.left );
	my_fun.h = (rect.bottom - rect.top );

	dialog2.a = 1;
	dialog2.b = 1;
	dialog2.s = 0.1*(my_fun.w);

	dialog2.DoModal();
	int a = dialog2.a;
	int b = dialog2.b;
	int s = dialog2.s;

	COLORREF color1 = RGB(0, 0, 0);
	COLORREF color2 = RGB(255, 255, 255);
	int color = 1;

	my_fun = func(a, b, s);
	my_color = getColor(color1, color2, color);
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
	dialog2.DoModal();
	if (my_fun.a != dialog2.a || my_fun.b != dialog2.b || my_fun.s != dialog2.s) {
		Invalidate();
	}
	my_fun.a = dialog2.a;
	my_fun.b = dialog2.b;
	my_fun.s = dialog2.s;
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




void CMFCApplication_in_classView::OnOpenValues()
{
	// TODO: Add your command handler code here
	open_mode = true;
	Invalidate();
}

void CMFCApplication_in_classView::OnOpenZeros()
{
	// TODO: Add your command handler code here
	open_mode = false;
	Invalidate();
}


void CMFCApplication_in_classView::OnUpdateValues(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(open_mode);
	my_color.color_type = 1;
}


void CMFCApplication_in_classView::OnUpdateZeros(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(!open_mode);
	my_color.color_type = -1;
}




void CMFCApplication_in_classView::setColor1() {
	if (dialog_color_1.DoModal() == IDOK) {
		my_color.color1 = dialog_color_1.GetColor();
		Invalidate();
	}
}

void CMFCApplication_in_classView::setColor2() {

	if (dialog_color_2.DoModal() == IDOK) {
		my_color.color2 = dialog_color_2.GetColor();
		Invalidate();
	}
}




