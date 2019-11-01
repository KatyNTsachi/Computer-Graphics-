
// MFCApplication_in_class.h : main header file for the MFCApplication_in_class application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCApplication_in_classApp:
// See MFCApplication_in_class.cpp for the implementation of this class
//

class CMFCApplication_in_classApp : public CWinApp
{
public:
	CMFCApplication_in_classApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication_in_classApp theApp;
