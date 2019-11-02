
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

	bool open;
	int a, b,s,color;
	func my_fun;
	getColor my_color;




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
};

#ifndef _DEBUG  // debug version in MFCApplication_in_classView.cpp
inline CMFCApplication_in_classDoc* CMFCApplication_in_classView::GetDocument() const
   { return reinterpret_cast<CMFCApplication_in_classDoc*>(m_pDocument); }
#endif

