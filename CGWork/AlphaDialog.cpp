// AlphaDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CGWork.h"
#include "AlphaDialog.h"
#include "afxdialogex.h"


// AlphaDialog dialog

IMPLEMENT_DYNAMIC(AlphaDialog, CDialogEx)

AlphaDialog::AlphaDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

AlphaDialog::~AlphaDialog()
{
}

void AlphaDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LIGHT_COLOR_B, alpha);
}

double AlphaDialog::getAlpha()
{
	return alpha;
}

BEGIN_MESSAGE_MAP(AlphaDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &AlphaDialog::OnEnChangeEdit1)
END_MESSAGE_MAP()


// AlphaDialog message handlers


void AlphaDialog::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
