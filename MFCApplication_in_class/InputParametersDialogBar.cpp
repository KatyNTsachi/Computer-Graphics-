// InputParametersDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication_in_class.h"
#include "InputParametersDialogBar.h"
#include "afxdialogex.h"


// InputParametersDialogBar dialog

IMPLEMENT_DYNAMIC(InputParametersDialogBar, CDialog)

InputParametersDialogBar::InputParametersDialogBar(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

InputParametersDialogBar::~InputParametersDialogBar()
{
}

void InputParametersDialogBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, id_a, a);
	DDX_Text(pDX, id_b, b);
	DDX_Text(pDX, id_s, s);
}


BEGIN_MESSAGE_MAP(InputParametersDialogBar, CDialog)
END_MESSAGE_MAP()


// InputParametersDialogBar message handlers
