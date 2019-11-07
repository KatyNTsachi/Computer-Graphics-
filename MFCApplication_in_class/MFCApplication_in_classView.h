
// MFCApplication_in_classView.h : interface of the CMFCApplication_in_classView class
//

#pragma once
#include "MyDialog.h"
#include "InputParametersDialogBar.h"

#include "func.h"
#include "getColor.h"

class CMFCApplication_in_classView : public CView
{
protected: // create from serialization only
	CMFCApplication_in_classView();
	DECLARE_DYNCREATE(CMFCApplication_in_classView)

// Attributes
public:
	CMFCApplication_in_classDoc* GetDocument() const;

	MyDialog dialog;
	InputParametersDialogBar dialog2;
	CColorDialog dialog_color_1, dialog_color_2;

	bool open;
	bool open_mode;
	func my_fun;
	getColor my_color;
	int a, b, s, color;
	COLORREF color1, color2;




// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	afx_msg void OnDialog();
	virtual ~CMFCApplication_in_classView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpencloseClose();
	afx_msg void OnOpencloseOpen();
	afx_msg void OnUpdateOpencloseOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpencloseClose(CCmdUI *pCmdUI);
	afx_msg void OnOpenValues();
	afx_msg void OnOpenZeros();
	afx_msg void OnUpdateValues(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZeros(CCmdUI *pCmdUI);
	afx_msg void setColor1();
	afx_msg void setColor2();


};

#ifndef _DEBUG  // debug version in MFCApplication_in_classView.cpp
inline CMFCApplication_in_classDoc* CMFCApplication_in_classView::GetDocument() const
   { return reinterpret_cast<CMFCApplication_in_classDoc*>(m_pDocument); }
#endif

