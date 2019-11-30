// InputParametersDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "CGWork.h"
#include "InputParametersDialogBar.h"
#include "afxdialogex.h"


// InputParametersDialogBar dialog

IMPLEMENT_DYNAMIC(InputParametersDialogBar, CDialogEx)

InputParametersDialogBar::InputParametersDialogBar(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FUNCTION_NUM, pParent)
{
	num_of_polygons = 20;
}


InputParametersDialogBar::~InputParametersDialogBar()
{
}

void InputParametersDialogBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUM, num_of_polygons);
}

int InputParametersDialogBar::getNumber()
{
	return num_of_polygons;
}


BEGIN_MESSAGE_MAP(InputParametersDialogBar, CDialogEx)
END_MESSAGE_MAP()



// InputParametersDialogBar message handlers
