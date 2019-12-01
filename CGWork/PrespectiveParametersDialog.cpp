// PrespectiveParametersDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CGWork.h"
#include "PrespectiveParametersDialog.h"
#include "afxdialogex.h"


// PrespectiveParametersDialog dialog

IMPLEMENT_DYNAMIC(PrespectiveParametersDialog, CDialogEx)

PrespectiveParametersDialog::PrespectiveParametersDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
	alpha = 1;
	d = 3;
}

PrespectiveParametersDialog::~PrespectiveParametersDialog()
{
}

void PrespectiveParametersDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, ID_ALPHA, alpha);
	DDX_Text(pDX, ID_D, d);
}

double PrespectiveParametersDialog::getAlpha()
{
	return alpha;
}

double PrespectiveParametersDialog::getD()
{
	return d;
}


BEGIN_MESSAGE_MAP(PrespectiveParametersDialog, CDialogEx)
END_MESSAGE_MAP()


// PrespectiveParametersDialog message handlers
