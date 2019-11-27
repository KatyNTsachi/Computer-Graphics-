// MouseSensitivity.cpp : implementation file
//

#include "stdafx.h"
#include "CGWork.h"
#include "MouseSensitivity.h"
#include "afxdialogex.h"
#include <sstream>
#include <iostream>
#include <string.h>


// MouseSensitivity dialog

IMPLEMENT_DYNAMIC(MouseSensitivity, CDialogEx)

MouseSensitivity::MouseSensitivity(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOUSE_SENSITIVITY, pParent)
{

}

MouseSensitivity::~MouseSensitivity()
{
}

void MouseSensitivity::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MouseSensitivity, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// MouseSensitivity message handlers


void MouseSensitivity::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void MouseSensitivity::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	CSliderCtrl* pSlider = reinterpret_cast<CSliderCtrl*>(pScrollBar);

	// Check which slider sent the notification  
	// Check what happened  
	sensitivity_scalar = pSlider->GetPos();
	
}

double MouseSensitivity::getSensitivityScalar()
{
	return (1 + sensitivity_scalar) / 10;
}